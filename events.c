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
		// exit(0);
	}
	else if (keystate[SDL_SCANCODE_TAB])
		all->layer = all->layer == 0 ? 1 : 0;
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

// void	map_click(t_object obj[MAP_WIDTH][MAP_HEIGHT], SDL_MouseButtonEvent *event,
// 				SDL_Texture *swap)
// {
// 	int	i;
// 	int j;
// 	int	dx;
// 	int	dy;

// 	i = 0;
// 	while(i < MAP_HEIGHT)
// 	{
// 		j = 0;
// 		while(j < MAP_WIDTH)
// 		{
// 			dx = event->x - obj[i][j].dstrect.x;
// 			dy = event->y - obj[i][j].dstrect.y;
// 			if(dx > 0 && dy > 0 && dx < OBJ_SIDE && dy < OBJ_SIDE)
// 				obj[i][j].texture = event->button == SDL_BUTTON_LEFT ? swap : NULL; 
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	map_click(SDL_MouseButtonEvent *event,
				t_line *line)
{
	line->x2 = event->x;
	line->y2 = event->y;

}

void	on_click(t_all *all, SDL_MouseButtonEvent *event)
{
	if (event->x >= 230)
	{
		if (all->line.state == 0)
		{
			all->line.x1 = event->x;
			all->line.y1 = event->y;
			all->line.state = 1;
		}
		map_click(event, &all->line);
	}
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