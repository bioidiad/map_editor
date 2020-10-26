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
		draw_line(all, vertex, &f);
}

void	draw_map(SDL_Renderer *rnd, t_sect *sect, t_all *all)
{
	int		i, j, k;
	t_xyz	s;
	t_xyz	f;
	t_sect *temp;

	i = 0;
	while(i < all->num_sectors)
	{
		//if (i == all->num_sectors - 1)
		//printf("sect # %d npoints = %d\nx, y = ", i, sect[i].npoints);
		j = 0;
		temp = &sect[i];
		// if (temp != all->swap)
		// 	SDL_SetRenderDrawColor(rnd, 255, 255, 255, 255);
		// else
			SDL_SetRenderDrawColor(rnd, 255, 2, 2, 255);
		while (j < temp->npoints)
		{
			
			//printf(" %d,%d  %d,%d\n", (int)temp->vertex[j].x, (int)temp->vertex[j].y, (int)temp->vertex[j +1].x, (int)temp->vertex[j +1].y);
			s = (t_xyz){(temp->vertex[j].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step),
				(temp->vertex[j].y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step),
					(temp->floor - all->mapsize.z/4) * all->step/2};
			k = j + 1; 
			f = (t_xyz){(temp->vertex[k].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step),
				(temp->vertex[k].y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step),
					(temp->floor - all->mapsize.z/4) * all->step/2};
			//isometric(all, temp, &s, all->rot);
			//isometric(all, temp, &f, all->rot);
			//if (i == all->num_sectors - 1)
			// printf("%f %f %f %f\n",s.x, s.y, f.x, f.y);
			//SDL_RenderDrawLine(all->sdl->renderer, s.x, s.y, f.x, f.y);
			draw_line(all, &s, &f);
			//draw_wall(all, &temp, j, &s);
			//draw_circle(rnd, (int)s.x, (int)s.y, 3);
			j++;
		}
		//printf("points = %d\n", temp->npoints);
		i++;
	}
	//exit(0);
}

void	draw_grid(t_all *all, SDL_Rect *area, int step)
{
	t_xy	c;

	c = (t_xy){(area->w / 2) % step, (area->h / 2) % step};
	SDL_SetRenderDrawColor(all->sdl->renderer, 255, 255, 255, 70);
	while (c.x <= area->w)
	{
		draw_line(all, &(t_xyz){c.x, 0, 0}, &(t_xyz){c.x, area->h});
		c.x += step;
	}
	c.x = 0;
	while (c.y <= area->h)
	{
		draw_line(all, &(t_xyz){c.x, c.y, 0}, &(t_xyz){area->w, c.y});
		c.y += step;
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
		draw_line(all, &s, &f);
		j++;
	}
}

void	draw_player(t_all *all, SDL_Renderer *rnd, t_player *player)
{
	SDL_Rect loc;

	if (all->player.picked == 0)
		loc = (SDL_Rect){(player->where.x + (all->area.w/(2 * all->step) - (all->mapsize.x/2))) * all->step,
		 (player->where.y + (all->area.w/(2 * all->step) - (all->mapsize.x/2))) * all->step,
	 		 all->step, all->step};
	else if (all->player.picked == 1)
		loc = (SDL_Rect){all->point.x * all->step, all->point.y * all->step, all->step, all->step};
	SDL_RenderCopy(rnd, player->picture, NULL, &loc);
}

void	draw_area(SDL_Renderer *rnd, t_all *all)
{
	draw_fill_rect(all, all->area, &(t_color){0, 0, 0, 255});
	if (SDL_RenderSetViewport(rnd, &all->area) != 0)
		exit(0);
	draw_grid(all, &all->area, all->step);
	draw_map(rnd, all->sectors, all);
	if (all->point.x != 0 && all->point.y != 0)
		draw_circle(all->sdl->renderer, all->point.x * all->step, all->point.y * all->step, 1);
	if (all->temp->npoints != 0)
		draw_temp(all, rnd, all->temp);
	draw_player(all, rnd, &all->player);
	
	// SDL_RenderPresent(rnd);
	
}

void	draw_all(t_all *all, SDL_Renderer *rnd, t_button *btn)
{
    int			i;
	Uint32 state;

	i = 0;
	if (SDL_RenderSetViewport(rnd, NULL) != 0)
		exit(0);
    SDL_RenderCopy(rnd, all->texture, NULL, NULL);
	while (i++ <= BUTTONS)
	{
        SDL_SetRenderDrawColor(rnd, 250, 250, 250, 70);
		if(all->buttons[i - 1].state == 1)
            draw_fill_rect(all, btn[i - 1].object.dstrect, &(t_color){250, 250, 250, 70});

			//SDL_RenderFillRect(rnd, &btn[i - 1].object.dstrect);
        SDL_RenderCopy(rnd, btn[i - 1].object.texture, NULL, &btn[i - 1].object.dstrect);
    } 
    // if(all->layer == 1)
		draw_area(rnd, all);
   
	// state = SDL_GetMouseState(&all->mouse.x, &all->mouse.y);
	//printf("1=%d\n2=%d\n3=%d\n4=%d\n", all->line.x1, all->line.y1, all->line.x2, all->line.y2);
	//draw_map(all->object[all->layer], rnd);
    SDL_RenderPresent(all->sdl->renderer);
}