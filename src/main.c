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
		draw_all(all, all->sdl->renderer, all->buttons); // отрисовка
	}
}

int main()
{
    t_all           *all;
    
    all = init_all(); // инициализация всех модулей
	load_map(all); //чтение и запись каты в структуры
	if (load_texture("filename", all) == 0) //загрузка текстур
		interact(all); // основная функция взаимодействия
}