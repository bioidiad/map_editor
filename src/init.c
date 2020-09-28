#include "editor.h"

static void			init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		error_and_close(__FILE__, __FUNCTION__);
	if (!(sdl->window = SDL_CreateWindow("Map Editor",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH,
			HEIGHT, SDL_WINDOW_SHOWN)))
	{
		SDL_Quit();
		error_and_close(__FILE__, __FUNCTION__);
	}
	
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
			SDL_RENDERER_ACCELERATED)))
	{
		SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		error_and_close(__FILE__, __FUNCTION__);
	}
	SDL_SetRenderDrawBlendMode(sdl->renderer, SDL_BLENDMODE_BLEND);
}

void	init_map(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while(i < 690)
	{
		j = 0;
		while(j < 876)
		{
			all->map[i][j].texture = NULL;
			//all->map[i][j].sector = NULL;
			j++;
		}
		i++;
	}
}

t_all    *init_all()
{
	t_all	*all;

    all = (t_all*)malloc(sizeof(t_all));
	all->sdl = (t_sdl*)malloc(sizeof(t_sdl));
    //all->map = (char*)malloc(sizeof(char) * (MAP_WIDTH * MAP_HEIGHT * MAP_ELEMENTS) + 1);
    init_sdl(all->sdl);
	all->angle = 20;
	all->rot = (t_xyz){45, 0, 0};
	// all->layer = 0; // слои, возможно не понадобятся
	all->mouse.z = 0; // переменная нажатия ЛКМ
	all->area = (SDL_Rect){319, 4, 876, 690}; // Область карты
	init_map(all);
	return(all);
}