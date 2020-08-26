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
	Uint32 state;

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
        draw_map(all->object[all->layer - 1], rnd);
        SDL_SetRenderDrawColor(rnd, 250, 250, 250, 200);
        SDL_RenderFillRect(rnd, &all->area);
    }
	state = SDL_GetMouseState(&all->line.x2, &all->line.y2);
	SDL_RenderDrawLine(all->sdl->renderer, all->line.x1, all->line.y1, all->line.x2, all->line.y2);
	printf("1=%d\n2=%d\n3=%d\n4=%d\n", all->line.x1, all->line.y1, all->line.x2, all->line.y2);
	draw_map(all->object[all->layer], rnd);
    SDL_RenderPresent(all->sdl->renderer);
}