#include "editor.h"

void	draw_map(t_object obj[MAP_HEIGHT][MAP_WIDTH], SDL_Renderer *rnd)
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
			if(obj[i][j].texture != NULL)
				SDL_RenderCopy(rnd, obj[i][j].texture, NULL, &obj[i][j].dstrect);
			j++;
		}
		i++;
	}
}

void	draw_all(t_all *all, SDL_Renderer *rnd, t_button *btn)
{
    int			i;

	i = 0;
    SDL_RenderCopy(rnd, all->texture, NULL, NULL);
	while (i++ <= BUTTONS)
	{
        SDL_SetRenderDrawColor(rnd, 250, 250, 250, 70);
		if(all->buttons[i - 1].state == 1)
            SDL_RenderFillRect(rnd, &btn[i - 1].object.dstrect);
        SDL_RenderCopy(rnd, btn[i - 1].object.texture, NULL, &btn[i - 1].object.dstrect);
    } 
    if(all->layer == 1)
    {
        draw_map(all->object[0], rnd);
        SDL_SetRenderDrawColor(rnd, 250, 250, 250, 200);
        SDL_RenderFillRect(rnd, &all->area);
    }
	draw_map(all->object[all->layer], rnd);
    SDL_RenderPresent(all->sdl->renderer);
}