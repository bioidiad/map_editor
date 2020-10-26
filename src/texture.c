#include "editor.h"

SDL_Surface	*get_texture(char *file, t_sdl *sdl)
{
	SDL_Surface		*surface;
    // SDL_Texture     *texture;
    char            *dir;

    dir = (char*)malloc(sizeof(char) * (ft_strlen(file) + 10));
    dir = ft_strjoin("textures/", file);
	if(!(surface = SDL_LoadBMP(dir)))
        error_and_close(__FILE__, __FUNCTION__);
    // if(!(texture = SDL_CreateTextureFromSurface(sdl->renderer, surface)))
    //     error_and_close(__FILE__, __FUNCTION__);
    free(dir);
    // SDL_FreeSurface(surface);
	// return (texture);
    return(surface);
}

int     load_buttons(t_all *all)
{
    char    *name;
    int     i;
    
    i = 0;
    name = NULL;
    while (++i <= BUTTONS)
    {
        all->buttons[i - 1].object.texture = get_texture(name = 
            ft_strjoin(ft_itoa(i), ".bmp"), all->sdl); 
        all->buttons[i - 1].object.dstrect.x = (i % 2 == 0 ? 140 : 40);
        all->buttons[i - 1].object.dstrect.y = (i - i / 2) * (PICT_HEIGHT + 30);
        all->buttons[i - 1].object.dstrect.w = PICT_WIDTH;
        all->buttons[i - 1].object.dstrect.h = PICT_HEIGHT;
        all->buttons[i - 1].state = 0;
    }
    return (1);
}

int     load_player(t_all *all)
{
    if(!(all->player.picture = get_texture("player.bmp", all->sdl)))
        return(0);
    return(1);
}

int     load_texture(t_all *all)
{
    if(!(all->texture = get_texture("plain.bmp", all->sdl)))
        error_and_close(__FILE__, __FUNCTION__);
    if (!(load_buttons(all)))
        error_and_close(__FILE__, __FUNCTION__);
    if (!(load_player(all)))
        error_and_close(__FILE__, __FUNCTION__);
    return (0);
}