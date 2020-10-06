#include "editor.h"

void	key_press(t_all *all)
{
	const Uint8	*keystate;

	keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
	{
		SDL_DestroyTexture(all->texture);
    	SDL_DestroyRenderer(all->sdl->renderer);
    	SDL_DestroyWindow(all->sdl->window);
	    SDL_Quit();
		free(all->sectors);
		free(all->sdl);
		free(all);
		exit(0);
	}
	// else if (keystate[SDL_SCANCODE_TAB])
	// 	all->layer = all->layer == 0 ? 1 : 0;
	else if (keystate[SDL_SCANCODE_RIGHT])
		all->rot.x += 1;
	else if (keystate[SDL_SCANCODE_LEFT])
		all->rot.x -= 1;
	else if (keystate[SDL_SCANCODE_UP])
		all->rot.y += 1;
	else if (keystate[SDL_SCANCODE_DOWN])
		all->rot.y -=1;
}

void	button_click(t_button *buttons, SDL_MouseButtonEvent *event)
{
	int	i;
	int	dx;
	int	dy;

	i = 0;
	while(i < BUTTONS)
	{
		buttons[i].state = 0;
		dx = event->x - buttons[i].object.dstrect.x;
		dy = event->y - buttons[i].object.dstrect.y;
		if(dx > 0 && dy > 0 && dx < PICT_WIDTH && dy < PICT_HEIGHT)
		{
			buttons[i].state = 1;
			buttons->swap = buttons[i].object.texture;
		}
		i++;
	}
}

void	map_click(t_xyz *mouse, t_sect *sector, t_all *all)
{
	int x;
	int y;
	int i;

	x = (int)mouse->x;
	y = (int)mouse->y;
	i = 0;
	if(sector)
	{
			all->swap = sector;
			printf("x = %d\ny = %d\nSector = %d:%d\n", x, y,
			(int)all->swap->vertex->x, (int)all->swap->vertex->y);
	}
	
	
}

void	on_mouse(t_all *all, SDL_MouseButtonEvent *event)
{
	SDL_Rect	*temp;

	temp = &all->area;
	if (event->x >= temp->x && event->x <= (temp->x + temp->w) &&
			event->y >= temp->y && event->y <= (temp->y + temp->h) &&
				all->mouse.z == 1)
	{
		all->mouse = (t_xyz){event->x - temp->x, event->y - temp->y};//пишем координаты мыши на карте
		map_click(&all->mouse, (all->map[(int)all->mouse.y][(int)all->mouse.x].sector), all);
	}
	else
		button_click(all->buttons, event); // обработка кликов на панели управления

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