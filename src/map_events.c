#include "editor.h"

void    new_sector(t_all *all, int x, int y)
{
    int i = 0;
    if(all->temp->npoints != 0)
        all->temp->vertex = ft_realloc(all->temp->vertex, (++all->temp->npoints) * sizeof(all->temp->vertex));
    else
        all->temp->vertex = malloc((++all->temp->npoints) * sizeof(all->temp->vertex));
	all->temp->vertex[all->temp->npoints - 1] = (t_xy){x, y};
	if (all->temp->vertex[0].x == x && all->temp->vertex[0].y == y && all->temp->npoints != 1)
	{
		all->sectors = ft_realloc(all->sectors, ++all->num_sectors * sizeof(*all->sectors));
		all->sectors[all->num_sectors - 1].vertex = malloc(sizeof(all->temp->vertex) * all->temp->npoints);
		ft_memcpy(&all->sectors[all->num_sectors - 1], &all->temp, sizeof(all->temp));
		ft_memcpy(&all->sectors[all->num_sectors - 1].vertex, &all->temp->vertex, 
		 	(sizeof(all->temp->vertex) * all->temp->npoints));
		ft_memdel((void*)&all->temp->vertex);
		all->temp->npoints = 0;
	}	
	
/**********************test**************/
		// while( i < all->temp.npoints)
		// {
		// 	printf("vertex %d = %d, %d\n", i, (int)all->sectors[all->num_sectors - 1].vertex[i].x, 
		// 		(int)all->sectors[all->num_sectors - 1].vertex[i].y);
		// 	i++;
		// }
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
		all->temp->floor = 0;
        all->temp->ceil = 10;
		all->temp->neighbors = NULL;
        new_sector(all, x, y);
		printf("x = %d\ny = %d\n", x, y);
		//draw_sector(all, &all->edit, x, y);
	}
    else if(all->buttons[1].state == 1)
    {
		// set_portal(all, x, y);
	}
    else if(all->buttons[2].state == 1)
    {
		// set_player(all, x, y);
	}
    else if(all->buttons[3].state == 1)
    {
		// set_sprite(all, x, y);
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