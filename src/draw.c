#include "editor.h"

void	draw_circle(SDL_Renderer *rnd, int x, int y, int r)
{
	int 	i;
	float	angle;
	float dx;
	float dy;
	int f;
	//printf("x:y = %d : %d\n", x, y);
	
	f = 0;
	while (f++ <= r)
	{
		i = 0;
		while (i++ < 50)
		{
			angle = (2 * 3.14 * i) / 50;
			dx = r * cosf(angle);
			dy = r * sinf(angle);
			SDL_RenderDrawPoint(rnd, x + dx, y + dy);
		}
	}
}

void	line_sector(t_all *all, t_sect *sect, t_xyz *start, t_xyz *fin)
{
	float		dx;
	float		dy;
	int	l;
	int i;
	float x, y;

	l = (int)fmax(abs((int)start->x - (int)fin->x), abs((int)start->y - (int)fin->y));
	dx = (fin->x - start->x) / l;
	dy = (fin->y - start->y) / l;
	x = (int)(start->x);
	y = (int)(start->y); 
	i = 0;

	while (i < l)
	{
		x = x + dx;
		y = y + dy;
		i++;
		SDL_RenderDrawPoint(all->sdl->renderer, (int)x, (int)y);
		if (x > 1 && y > 1 && x < all->area.w && y < all->area.h - 1)
		{
			all->map[(int)y][(int)x].sector = sect;
			all->map[(int)y + 1][(int)x + 1].sector = sect;
			all->map[(int)y - 1][(int)x - 1].sector = sect;//записываем вершины по координатам пикселей
		//printf("sectx = %f:%f\n", all->map[(int)y][(int)x].sector->vertex->x, sect->vertex->y);
		}
	} 	
}

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
		line_sector(all, sect, vertex, &f);
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
		// printf("%d and sect n =  %d x, y = ", i, sect[i].npoints);
		j = 0;
		temp = &sect[i];
		if (temp != all->swap)
			SDL_SetRenderDrawColor(rnd, 255, 255, 255, 255);
		else
			SDL_SetRenderDrawColor(rnd, 255, 2, 2, 255);
		while (j < temp->npoints)
		{
			// printf(" %d,%d", (int)temp->vertex[j].x, (int)temp->vertex[j].y);
			s = (t_xyz){(temp->vertex[j].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step),
				(temp->vertex[j].y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step),
					(temp->floor - all->mapsize.z/4) * all->step/2};
			f = (t_xyz){(temp->vertex[j + 1].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step),
				(temp->vertex[j + 1].y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step),
					(temp->floor - all->mapsize.z/4) * all->step/2};
			//isometric(all, temp, &s, all->rot);
			//isometric(all, temp, &f, all->rot);
			line_sector(all, temp, &s, &f);
			//draw_wall(all, &temp, j, &s);
			//draw_circle(rnd, (int)s.x, (int)s.y, 3);
			j++;
		}
		// printf("\n");
		i++;
	}
	//exit(0);
}

void	draw_grid(SDL_Renderer *rnd, SDL_Rect *area, int step)
{
	t_xy	c;

	// *step = area->h / 30;
	c = (t_xy){0, 0};
	SDL_SetRenderDrawColor(rnd, 255, 255, 255, 70);
	while (c.x <= area->w)
	{
		SDL_RenderDrawLine(rnd, c.x, c.y, c.x, area->h);
		c.x += step;
	}
	c.x = 0;
	while (c.y <= area->h)
	{
		SDL_RenderDrawLine(rnd, c.x, c.y, area->w, c.y);
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
		line_sector(all, temp, &s, &f);
		j++;
	}
}

void	draw_area(SDL_Renderer *rnd, t_all *all)
{
	if (SDL_RenderSetViewport(rnd, &all->area) != 0)
		exit(0);
	SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
	SDL_RenderFillRect(rnd, NULL);
	draw_grid(rnd, &all->area, all->step);
	draw_map(rnd, all->sectors, all);
	if (all->point.x != 0 && all->point.y != 0)
		draw_circle(all->sdl->renderer, all->point.x * all->step, all->point.y * all->step, 1);
	if (all->temp->npoints != 0)
		draw_temp(all, rnd, all->temp);
	
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
            SDL_RenderFillRect(rnd, &btn[i - 1].object.dstrect);
        SDL_RenderCopy(rnd, btn[i - 1].object.texture, NULL, &btn[i - 1].object.dstrect);
    } 
    // if(all->layer == 1)
		draw_area(rnd, all);
   
	// state = SDL_GetMouseState(&all->mouse.x, &all->mouse.y);
	//printf("1=%d\n2=%d\n3=%d\n4=%d\n", all->line.x1, all->line.y1, all->line.x2, all->line.y2);
	//draw_map(all->object[all->layer], rnd);
    SDL_RenderPresent(all->sdl->renderer);
}