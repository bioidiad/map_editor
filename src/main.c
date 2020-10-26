#include "editor.h"

void	interact(t_all *all)
{
	SDL_Event		event;
	Uint32			cur_time;
	Uint32			last_time;

	while ((last_time = SDL_GetTicks()))
	{
		while (SDL_PollEvent(&event)) // отслеживаем события
		{
			on_event(all, &event); // обработчик событий
			cur_time = SDL_GetTicks();
			if (cur_time - last_time > FPS)
				break ;
		}
		if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP || event.type == SDL_MOUSEMOTION
			|| event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN)
		{
			draw_all(all, all->sdl->renderer, all->buttons);
			event.type = 0; // отрисовка
		}
	}
}

int main(int ac, char **av)
{
    t_all           *all;
	
	if(ac > 2)
	{
		printf("Enter correct map name or new map name!\n");
		exit(0);
	}
    all = init_all(); // инициализация всех модулей
	if (load_map(av[1], all) != 0)
		error_and_close(__FILE__, __FUNCTION__);
	if (load_texture(all) != 0)
		error_and_close(__FILE__, __FUNCTION__); //загрузка текстур
	draw_texture(all->sdl->renderer, (SDL_Rect){0,0, WIDTH, HEIGHT}, all->texture);
	
	interact(all); // основная функция взаимодействия
	write_map(av[1], all);
	return (0);
}