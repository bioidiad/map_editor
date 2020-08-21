#include "editor.h"

SDL_Surface	*get_surface(char *file)
{
	SDL_Surface		*surface;
    char            *dir;

    dir = (char*)malloc(sizeof(char) * (ft_strlen(file) + 10));
    dir = ft_strjoin("textures/", file);
	if(!(surface = SDL_LoadBMP(dir)))
        error_and_close(__FILE__, __FUNCTION__);
    free(dir);
	return (surface);
}

int     load_buttons(t_all *all)
{
    char    *name;
    int     i;
    
    i = 0;
    name = NULL;
    while (++i <= BUTTONS)
    {
        all->buttons[i - 1].object.surface = get_surface(name = 
            ft_strjoin(ft_itoa(i), ".bmp")); 
        all->buttons[i - 1].object.dstrect.x = (i % 2 == 0 ? 140 : 40);
        all->buttons[i - 1].object.dstrect.y = (i - i / 2) * (PICT_HEIGHT + 30);
        all->buttons[i - 1].object.dstrect.w = PICT_WIDTH;
        all->buttons[i - 1].object.dstrect.h = PICT_HEIGHT;
        all->buttons[i - 1].state = 0;
    }
    return (1);
}

int     load_texture(char *file, t_all *all)
{
    if(!(all->background->surface = get_surface("plain.bmp")))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(all->texture = SDL_CreateTextureFromSurface(all->sdl->renderer,
                 all->background->surface)))///////
        error_and_close(__FILE__, __FUNCTION__);
    if (!(load_buttons(all)))
        error_and_close(__FILE__, __FUNCTION__);   
    return (0);
}