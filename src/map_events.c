#include "editor.h"

void    new_sector(t_all *all, int x, int y)
{
    int i = 0;

	all->min_coord.x = x < all->min_coord.x ? x : all->min_coord.x;
	all->min_coord.y = y < all->min_coord.y ? y : all->min_coord.y;
	all->max_coord.x = x > all->max_coord.x ? x : all->max_coord.x;
	all->max_coord.y = y > all->max_coord.y ? y : all->max_coord.y;

    all->temp->vertex = ft_realloc(all->temp->vertex, (++all->temp->npoints) * sizeof(t_xy));
	all->temp->vertex[all->temp->npoints - 1] = (t_xy){x, y};
	if (all->temp->vertex[0].x == x && all->temp->vertex[0].y == y && all->temp->npoints != 1)
	{
		all->sectors = ft_realloc(all->sectors, ++all->num_sectors * sizeof(t_sect));
		all->sectors[all->num_sectors - 1].vertex = malloc(sizeof(t_xy) * all->temp->npoints);
		all->sectors[all->num_sectors - 1].npoints = all->temp->npoints;
		all->sectors[all->num_sectors - 1].floor = all->temp->floor;
		all->sectors[all->num_sectors - 1].ceil = all->temp->ceil; 
		while( i < all->temp->npoints)
		{
			all->sectors[all->num_sectors - 1].vertex[i] = all->temp->vertex[i];
			i++;
		}
		all->sectors[all->num_sectors - 1].npoints--;
		get_neighbours(&all->sectors[all->num_sectors -1], all, all->num_sectors);
		// all->sectors[all->num_sectors - 1].vertex[0] = (t_xy){all->temp->vertex[0].x, all->temp->vertex[0].y};
		printf("%p\n%p\n", all->temp->vertex, all->sectors[all->num_sectors-1].vertex);
		ft_memdel((void*)&all->temp->vertex);
		all->temp->npoints = 0;
		
	
/**********************test**************/
		// i = 0;
		// while( i < all->sectors[all->num_sectors - 1].npoints)
		// {
		// 	printf("vertex %d = %d, %d, points = %d\n", i, (int)all->sectors[all->num_sectors - 1].vertex[i].x, 
		// 		(int)all->sectors[all->num_sectors - 1].vertex[i].y, 
		// 		(int)all->sectors[all->num_sectors - 1].npoints);
		// 	i++;
		// }
		// exit(0);
	}
}

void    set_player(t_all *all, int x, int y)
{
	all->player.where = (t_xyz){x, y, 0};
	all->player.picked = 0;
	all->buttons[1].state = 0;
}

void	map_click(t_xyz *mouse, t_sect *sector, t_all *all)
{
	int x;
	int y;
	int i;

	x = all->point.x - (all->area.w/(2 * all->step) - (all->mapsize.x/2));
	y = all->point.y - (all->area.h/(2 * all->step) - (all->mapsize.y/2));
	i = 0;

	if(all->buttons[0].state == 1)
	{
		all->temp->floor = 0; //(int)all->set_floors.x;
        all->temp->ceil = 15;//(int)all->set_floors.y;
		all->temp->neighbors = NULL;
        new_sector(all, x, y);
		// printf("x = %d\ny = %d\n", x, y);
		//draw_sector(all, &all->edit, x, y);
	}
    else if(all->buttons[1].state == 1)
    {
		all->player.where.z = 0;
		set_player(all, x, y);
	}
    else if(all->buttons[2].state == 1)
    {
		// all->draw_floors.x -= all->draw_floors.x > 0 ?  1 : 0;
		// all->buttons[2].state = 0;
	}
    else if(all->buttons[3].state == 1)
    {
		// all->draw_floors.x += all->draw_floors.x < all->mapsize.z ?  1 : 0;
		// all->buttons[3].state = 0;
	}
    else if(all->buttons[4].state == 1)
    {
		// set_texture(all, x, y);
	}
	// else if(sector)
	// {
	// 		all->swap = sector;
	// 		printf("x = %d\ny = %d\nSector = %d:%d\n", x, y,
	// 		(int)all->swap->vertex->x, (int)all->swap->vertex->y);
	// }
	else
	{
		printf("x = %d\ny = %d\n", x, y);
	}
}