#include "editor.h"

void	key_press(t_all *all)
{
	const Uint8	*keystate;

	keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
	{
		//SDL_DestroyTexture(all->texture);
    	SDL_DestroyRenderer(all->sdl->renderer);
    	SDL_DestroyWindow(all->sdl->window);
	    SDL_Quit();
		free(all->sectors);
		free(all->sdl);
		free(all);
		exit(0);
	}
	else if (keystate[SDL_SCANCODE_TAB])
		write_map("new", all);
	else if (keystate[SDL_SCANCODE_RIGHT])
		all->step += 1;
	else if (keystate[SDL_SCANCODE_LEFT])
		all->step -= (all->step > 1) ? 1 : 0;
	else if (keystate[SDL_SCANCODE_I])
		all->iso = (all->iso == 0) ? 1 : 0;
	// else if (keystate[SDL_SCANCODE_UP])
	// 	all->rot.y += 1;
	// else if (keystate[SDL_SCANCODE_DOWN])
	// 	all->rot.y -=1;
}

void	button_click(t_all *all, t_button *buttons, SDL_MouseButtonEvent *event)
{
	int	i;
	int	dx;
	int	dy;

	i = 0;
	while(i < BUTTONS && all->mouse.z == 1)
	{
		dx = event->x - buttons[i].dstrect.x;
		dy = event->y - buttons[i].dstrect.y;
		if(dx > 0 && dy > 0 && dx < buttons[i].dstrect.w && dy < buttons[i].dstrect.h)
		{
			buttons[i].state = buttons[i].state == 1 ? 0 : 1;
			all->edit.function = i;
			//buttons->swap = buttons[i].object.texture;
		}
		else
			buttons[i].state = 0;		
		i++;
	}
	all->player.picked = buttons[1].state == 1 ? 1 : 0;
}

t_xyz	coordinator(t_all *all, int x, int y, t_xyz rot)
{
	t_xyz temp;
	int z;
	// rot = (t_xyz){-rot.x, -rot.y, -rot.z};

	// z = 0;
	// rot = (t_xyz){(M_PI / 25 * rot.x), (M_PI / 25 * rot.y), (M_PI / 135 * rot.z) * -1};
	// temp.y = y * cos(rot.x) + z * sin(rot.x) - all->area.h/2;
	// temp.z = -(y * sin(rot.x)) + z * cos(rot.x);
	// y = temp.y;
	// z = temp.z;
	// temp.x = x * cos(rot.y) + z * sin(rot.y) - all->area.w/2;
	// temp.z = -(x * sin(rot.y)) + z * cos(rot.y);
	// x = temp.x;
	// z = temp.z;
	// temp.x = x * cos(rot.z) - y * sin(rot.z);
	// temp.y = x * sin(rot.z) + y * cos(rot.z);
	temp.x = x / all->step - (all->area.w/all->step/2 - all->mapsize.x/2);
	temp.y = y / all->step - (all->area.h/all->step/2 - all->mapsize.y/2);
	temp.z = z / all->step + all->mapsize.z;
	return(temp);
}

// void	draw_sector(t_all *all, t_edit *new, int x, int y)
// {
// 	t_xyz n = coordinator(all, x, y, all->rot);
// 	printf("x = %d, y = %d\n", n.x, n.y);
// }


void	closest_point(t_all *all, t_xyint point, t_xyz mouse)
{
	t_xy	   c;

	c = (t_xy){(all->area.w / 2) % all->step, (all->area.h / 2) % all->step};
	all->point.x = round(((float)point.x - all->area.x - c.x) / all->step);
	all->point.y = round(((float)point.y - all->area.y - c.y) / all->step);
}

void	on_mouse(t_all *all, SDL_MouseButtonEvent *event)
{
	SDL_Rect	*temp;
	int			x;
	int			y;

	x = all->mouse.x;
	y = all->mouse.y;
	temp = &all->area;

	if (event->x >= temp->x && event->x <= (temp->x + temp->w) &&
			event->y >= temp->y && event->y <= (temp->y + temp->h))// &&
				// all->mouse.z == 0 && all->buttons[0].state == 1)
	{
		SDL_GetMouseState(&all->point.x, &all->point.y);
		closest_point(all, all->point, all->mouse);
	
		if (all->mouse.z == 1)
		{
			all->mouse = (t_xyz){event->x - temp->x, event->y - temp->y};//пишем координаты мыши на карте
			map_click(&all->mouse, (all->map[y][x].sector), all);
		}
	}
	else
		button_click(all, all->buttons, event); // обработка кликов на панели управления
		// else if (event->x >= temp->x && event->x <= (temp->x + temp->w) &&
		// 		event->y >= temp->y && event->y <= (temp->y + temp->h))// &&
		// 			// all->mouse.z == 0 && all->buttons[0].state == 1)
		// {
		// 	SDL_GetMouseState(&all->point.x, &all->point.y);
		// 	closest_point(all, all->point, all->mouse);
		// }
	
}

void	on_event(t_all *all, SDL_Event *event)
{
	if (event->key.type == SDL_KEYDOWN)
		key_press(all); // обработка событий клавиатуры
	else if (event->button.type == SDL_MOUSEBUTTONDOWN)
		all->mouse.z = 1;
	else if (event->button.type == SDL_MOUSEBUTTONUP)
		all->mouse.z = 0;
	on_mouse(all, &event->button); // обаботка событий мыши
}