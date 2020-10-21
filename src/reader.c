#include "editor.h"
// #include <sys/stat.h>

void	get_map_whl(t_all *all)
{
	int i;
	int x, y, z;

	i = 0;
	while(i < all->num_sectors)
	{
		x = (int)all->sectors[i].vertex->x;
		y = (int)all->sectors[i].vertex->y;
		z = (int)all->sectors[i].ceil;
		// all->map_whl.x = all->map_whl.x < x ? x : all->map_whl.x;
		// all->map_whl.y = all->map_whl.y < y ? y : all->map_whl.y;
		// all->map_whl.z = all->map_whl.z < z ? z : all->map_whl.z;
		i++;
	}
}


int	load_map(char *name, t_all *all)
{
	char	*line;
	char	word[6];
	char	*ptr;
	int		fd;

	all->sectors = NULL;
	if (name)
		fd = open(ft_strjoin(name, ".txt"), O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	else
		fd = open("new_map.txt", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		perror(name);
		exit(1);
	}
	t_xy 	*vert = NULL;
	t_xy	v;
	int n, m, NumVertices = 0;

	line = (char*)malloc(sizeof(char) * BUFF_SIZE + 1);
	all->mapsize = (t_xyz){0, 0, 0};

	while (get_next_line(fd, &line))
		switch (sscanf(line, "%32s%n", word, &n) == 1 ? word[0] : '\0')
		/*считывает в word строку, в n - кол-во символов в строке
		если в строке более 32х символов - следующий вызов с того же места*/
		{
		case 'v': // если word[0]=='v'
			for (sscanf(line += n, "%f%n", &v.y, &n); sscanf(line += n, "%f%n", &v.x, &n) == 1;)
			/* пока сканф возвращает 1, считывает в v.x и v.y целые числа, в n - количество считанных символов
			сдвигаясь на n символов перед считыванием */
			{
				vert = ft_realloc(vert, ++NumVertices * sizeof(*vert));
				vert[NumVertices - 1] = v;
			
                //NumVertices общее количество вершин
                //vert массив всех вершин где к примеру строка vertex	0	0 6 28 хранится как 0 0, 0 6, 0 28
                //никаких разделителей между строк нет
				all->mapsize.x = v.x > all->mapsize.x ? v.x : all->mapsize.x;
				all->mapsize.y = v.y > all->mapsize.y ? v.y : all->mapsize.y;
			}
			break;
		case 's': // sector
			all->sectors = ft_realloc(all->sectors, ++all->num_sectors * sizeof(*all->sectors));
			t_sect *sect = &all->sectors[all->num_sectors - 1];
			int *num = NULL;
			//считывает пол и потолок
			sscanf(line += n, "%f%f%n", &sect->floor, &sect->ceil, &n);
			all->mapsize.z = sect->ceil > all->mapsize.z ? sect->ceil : all->mapsize.z;
			for (m = 0; sscanf(line += n, "%32s%n", word, &n) == 1 && word[0] != '#';)
			{
				num = ft_realloc(num, ++m * sizeof(*num));
				num[m - 1] = ft_atoi(word);
                //m хранит количество вершин + количество соседних секторов, причем первое == второму
                //num хранит все числа принадлижащие одному сектору, кроме пола и потолка
                //никаких разделителей между строк нет
			}

			sect->npoints = m /= 2; //количество соседей и вершин этого сектора (всегда одинаково)
			sect->neighbors = malloc((m) * sizeof(*sect->neighbors));
			sect->vertex = malloc((m + 1) * sizeof(*sect->vertex));
			//цикл запишет правую половину num массива, то есть соседей
			for (n = 0; n < m; ++n)
				sect->neighbors[n] = num[m + n];
			for (n = 0; n < m; ++n)
			    //в num[n] перечислены номера вершин сектора
			    //в vert[num[n]] получаем координаты вершины по её номеру
                sect->vertex[n + 1] = vert[num[n]];
			sect->vertex[0] = sect->vertex[m];
			//в sect->vertex первая и последняя координаты одинаковы, то есть вершины закольцованы
			free(num);
			break;
		case 'p':; // player
			float angle;
			sscanf(line += n, "%f %f %f %d", &v.x, &v.y, &angle, &n);
			all->player.where = (t_xyz){v.x, v.y, 0};
			all->player.velocity = (t_xyz){0, 0, 0};
			all->player.angle = angle;
			all->player.anglecos = 0;
			all->player.anglesin = 0;
			all->player.yaw = 0;
			all->player.sector = n;
			all->player.where.z = all->sectors[all->player.sector].floor + EYE_HEIGHT;
		}
	close(fd);
	free(vert);
	//get_map_whl(all);
	//printf("data loaded\nw = %f\nh = %f\nl = %f\n", all->map_whl.x, all->map_whl.y, all->map_whl.z);
	//printf("map width = %f\nmap lenght = %f\nmap height = %f\n", all->mapsize.x, all->mapsize.y, all->mapsize.z);
	return (0);
}