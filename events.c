#include "editor.h"

void	key_press(t_all *all)
{
	const Uint8	*keystate;

	keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
	{
		// sdl_quit(sdl);
		exit(0);
	}
	else if (keystate[SDL_SCANCODE_TAB])
		all->layer = all->layer == 0 ? 1 : 0;
	// draw_all(all);
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
			buttons[i].state = buttons[i].state == 0 ? 1 : 0;
			buttons->swap = buttons[i].object.surface;
		}
		i++;
	}
}

void	map_click(t_object obj[MAP_WIDTH][MAP_HEIGHT], SDL_MouseButtonEvent *event,
				SDL_Surface *swap)
{
	int	i;
	int j;
	int	dx;
	int	dy;

	i = 0;
	while(i < MAP_HEIGHT)
	{
		j = 0;
		while(j < MAP_WIDTH)
		{
			dx = event->x - obj[i][j].dstrect.x;
			dy = event->y - obj[i][j].dstrect.y;
			if(dx > 0 && dy > 0 && dx < OBJ_SIDE && dy < OBJ_SIDE)
				obj[i][j].surface = swap; 
			j++;
		}
		i++;
	}
}

void	on_click(t_all *all, SDL_MouseButtonEvent *event)
{
	if (event->x >= 230)
		map_click(all->object[all->layer], event, all->buttons->swap);
	else
		button_click(all->buttons, event);

}

void	on_event(t_all *all, SDL_Event *event)
{
	if (event->key.type == SDL_KEYDOWN)
		key_press(all);
	else if (event->button.type == SDL_MOUSEBUTTONDOWN)
		on_click(all, &event->button);
}