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

void	init_objects(t_all *all)
{
	int	i;
	int	j;
	int k;

	k = 0;
	while (k < LAYER)
	{
		i = 0;
		while(i < MAP_HEIGHT)
		{
			j = 0;
			while(j < MAP_WIDTH)
			{
				all->object[k][i][j].dstrect.x = 230 + (OBJ_SIDE * j);
				all->object[k][i][j].dstrect.y = 4 + (OBJ_SIDE * i);
				all->object[k][i][j].dstrect.h = OBJ_SIDE;
				all->object[k][i][j].dstrect.w = OBJ_SIDE;
				all->object[k][i][j].texture = NULL;
				j++;
			}
			i++;
		}
		k++;
	}
}

SDL_Rect	map_area()
{
	SDL_Rect area;

	area.x = 230;
	area.y = 4;
	area.h = 622;
	area.w = 628;

	return (area);
}

t_all    *init_all()
{
	t_all	*all;

    all = (t_all*)malloc(sizeof(t_all));
	all->sdl = (t_sdl*)malloc(sizeof(t_sdl));
    all->map = (char*)malloc(sizeof(char) * (MAP_WIDTH * MAP_HEIGHT * MAP_ELEMENTS) + 1);
    init_sdl(all->sdl);
	all->layer = 0;
	all->line.state = 0;
	all->area = map_area();
	init_objects(all);
	return(all);
}