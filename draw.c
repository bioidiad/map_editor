#include "editor.h"

void	draw_map(t_object obj[MAP_HEIGHT][MAP_WIDTH], SDL_Surface *screen)
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
			if(obj[i][j].surface != NULL)
				SDL_BlitScaled(obj[i][j].surface, NULL, 
        	screen, &obj[i][j].dstrect); 
			j++;
		}
		i++;
	}
}

void	draw_all(t_all *all)
{
	SDL_Surface *screen;
    int			i;

	i = 0;

    // if (!(screen = SDL_GetWindowSurface(all->sdl->window)))
    //     error_and_close(__FILE__, __FUNCTION__);
	// SDL_BlitSurface(all->background->surface, NULL, screen, NULL);
	// while (i++ <= BUTTONS)
	// {
	// 	if(all->buttons[i - 1].state == 1)
	// 		SDL_FillRect(screen, &all->buttons[i - 1].object.dstrect, 0xFFFFFF);
	// 	SDL_BlitScaled(all->buttons[i - 1].object.surface, NULL, 
    //     	screen, &all->buttons[i - 1].object.dstrect); // blit it to the screen
    // }
    // if(all->layer == 1)
    // {
    //     draw_map(all->object[0], screen);
    //     SDL_FillRect(screen, &all->area, SDL_MapRGBA(screen->format, 255, 255, 255, 25));
    // }
	// draw_map(all->object[all->layer], screen);
	// SDL_UpdateWindowSurface(all->sdl->window);
	///SDL_FreeSurface(screen);//      текстура будет удалена вместе с окном SDL

    SDL_RenderClear(all->sdl->renderer);
    SDL_RenderCopy(all->sdl->renderer, all->texture, NULL, NULL);
    SDL_RenderPresent(all->sdl->renderer);
}