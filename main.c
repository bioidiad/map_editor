#include "editor.h"

void	interact(t_all *all)
{
	SDL_Event		event;
	Uint32			cur_time;
	Uint32			last_time;

	while ((last_time = SDL_GetTicks()))
	{
		while (SDL_PollEvent(&event))
		{
			on_event(all, &event);
			cur_time = SDL_GetTicks();
			if (cur_time - last_time > FPS)
				break ;
		}
		draw_all(all, all->sdl->renderer, all->buttons);
	}
}

int main()
{
    t_all           *all;
    
    all = init_all();
	if (load_texture("filename", all) == 0)
		interact(all);
}