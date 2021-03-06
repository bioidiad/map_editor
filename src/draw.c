#include "editor.h"

t_xyz	isometric(t_all *all, t_sect *sect, t_xyz *start, t_xyz rot)
{
	t_xyz temp;

	rot = (t_xyz){(M_PI / 25 * rot.x), (M_PI / 25 * rot.y), (M_PI / 135 * rot.z) * -1};
	temp.y = all->area.h/2 + start->y * cos(rot.x) + start->z * sin(rot.x);
	temp.z = -(start->y * sin(rot.x)) + start->z * cos(rot.x);
	start->y = temp.y;
	start->z = temp.z;
	temp.x = all->area.w/2 + start->x * cos(rot.y) + start->z * sin(rot.y);
	temp.z = -(start->x * sin(rot.y)) + start->z * cos(rot.y);
	start->x = temp.x;
	start->z = temp.z;
	start->x -= all->area.w/2;
	start->y -= all->area.h/4; 
	start->z += all->mapsize.z/ 2;
	// temp.x = start->x * cos(rot.z) - start->y * sin(rot.z);
	// temp.y = start->x * sin(rot.z) + start->y * cos(rot.z);
	// start->x = temp.x;
	// start->y = temp.y;
}

void	draw_wall(t_all *all, t_sect *sect, int j, t_xyz *vertex)
{
	t_xyz f;

	f = (t_xyz){sect->vertex[j].x * all->step + (all->step * 5),
				sect->vertex[j].y * all->step + (all->step * 6), sect->ceil * all->step/2};
	//isometric(all, sect, &f, all->rot);
	//if (sect->floor == 0)
		draw_line(all, vertex, &f, all->color);
}

void	draw_map(SDL_Renderer *rnd, t_sect *sect, t_all *all)
{
	int		i, j;
	t_xyz	s;
	t_xyz	f;
	t_sect *temp;

	i = 0;
	while(i < all->num_sectors)
	{
		j = 0;
		temp = &sect[i];
		while (j < temp->npoints)
		{
			s = (t_xyz){(temp->vertex[j].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step),
				(temp->vertex[j].y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step),
					(temp->floor - all->mapsize.z/4) * all->step/2};
			f = (t_xyz){(temp->vertex[j + 1].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step),
				(temp->vertex[j + 1].y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step),
					(temp->floor - all->mapsize.z/4) * all->step/2};
			if (all->iso)
			{
				isometric(all, temp, &s, (t_xyz){10, 1, 1});
				isometric(all, temp, &f, (t_xyz){10, 1, 1});
			}
			all->color = (temp->neighbors[j] == -1 && j < temp->npoints) ? RED : BLUE;
			draw_line(all, &s, &f, all->color);
			draw_circle(rnd, (int)s.x, (int)s.y, 3);
			j++;
		}
		SDL_RenderPresent(all->sdl->renderer);
		i++;
	}
}



void	draw_temp(t_all *all, SDL_Renderer *rnd, t_sect *temp)
{
	t_xyz	s;
	t_xyz	f;
	int j = 0;
	int x = all->point.x - (all->area.w/(2 * all->step) - (all->mapsize.x/2));
	int y = all->point.y - (all->area.h/(2 * all->step) - (all->mapsize.y/2));

	while (j < temp->npoints)
	{
		if(j == temp->npoints - 1)
		{
			s = (t_xyz){(temp->vertex[j].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step),
			(temp->vertex[j].y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step),
				(temp->floor - all->mapsize.z/4) * all->step/2};
			f = (t_xyz){(x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step),
			(y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step),
				(temp->floor - all->mapsize.z/4) * all->step/2};
		}
		else
		{		// printf(" %d,%d", (int)temp->vertex[j].x, (int)temp->vertex[j].y);
			s = (t_xyz){(temp->vertex[j].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step),
				(temp->vertex[j].y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step),
					(temp->floor - all->mapsize.z/4) * all->step/2};
			f = (t_xyz){(temp->vertex[j + 1].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step),
				(temp->vertex[j + 1].y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step),
					(temp->floor - all->mapsize.z/4) * all->step/2};
		}
		draw_line(all, &s, &f, all->color);
		j++;
	}
}

void	draw_area(SDL_Renderer *rnd, t_all *all)
{
	t_xy	   c;

	c = (t_xy){(all->area.w / 2) % all->step, (all->area.h / 2) % all->step};
	draw_fill_rect(all, all->area, &(SDL_Color){0, 0, 0, 255});
	if (SDL_RenderSetViewport(rnd, &all->area) != 0)
		exit(0);
	draw_grid(all, &all->area, all->step);
	draw_map(rnd, all->sectors, all);
	if (all->point.x != 0 && all->point.y != 0)
		draw_circle(all->sdl->renderer, all->point.x * all->step + c.x, all->point.y * all->step + c.y, 1);
	if (all->temp->npoints != 0)
		draw_temp(all, rnd, all->temp);
	draw_player(all, rnd, &all->player, &c);
}

void	draw_all(t_all *all, SDL_Renderer *rnd, t_button *btn)
{
    int			i;
	Uint32 state;

	i = 0;
	if (SDL_RenderSetViewport(rnd, NULL) != 0)
		exit(0);
	// draw_texture(rnd, (SDL_Rect){0,0, WIDTH, HEIGHT}, all->texture);
	while (i < BUTTONS)
	{
		
		btn[i].color = (btn[i].state == 0) ? WHITE : RED;
		SDL_FreeSurface(btn[i].texture);
		btn[i].texture = get_text_surface(all, btn[i].title, btn[i].dstrect, btn[i].color);
		draw_texture(rnd, btn[i].dstrect, btn[i].texture);
		i++;
    } 
	draw_slider(all, &(SDL_Rect){50, 500, 100, 20}, 50, "floor heigt");
	draw_area(rnd, all);
    SDL_RenderPresent(all->sdl->renderer);
}