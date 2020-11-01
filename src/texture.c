#include "editor.h"

SDL_Surface     *get_texture(char *file, t_sdl *sdl)
{
	SDL_Surface		*surface;
    char            *dir;

    dir = (char*)malloc(sizeof(char) * (ft_strlen(file) + 10));
    dir = ft_strjoin("textures/", file);
	if(!(surface = SDL_LoadBMP(dir)))
        error_and_close(__FILE__, __FUNCTION__);
    free(dir);
    return(surface);
}
SDL_Surface	*get_text_surface(t_all *all, char *name, SDL_Rect target, SDL_Color color)
{
    SDL_Surface *text;
	int 		shift;
	int 		x;
    
	shift = 10 * ft_strlen(name);
    //text = SDL_CreateRGBSurface(1, target.w, target.h, 32 , 255, 255, 0, 0);
    if(!(text=TTF_RenderText_Blended(all->font, name, color)))
        printf("text printing error!\n");
	return(text);
}

int             load_buttons(t_all *all, t_button *buttons)
{
    SDL_Texture *tt;
    int i;

    buttons[0].dstrect = (SDL_Rect){50, 50, 200, 50};
    buttons[0].title = ft_strdup("NEW SECTOR");
    buttons[0].texture = get_text_surface(all, "NEW SECTOR", buttons[0].dstrect, BLACK);
    tt = SDL_CreateTextureFromSurface(all->sdl->renderer, buttons[0].texture);
    SDL_RenderCopy(all->sdl->renderer, tt, NULL, &buttons[0].dstrect);
    SDL_RenderPresent(all->sdl->renderer);
    buttons[1].dstrect = (SDL_Rect){50, 150, 200, 50};
    buttons[1].title = ft_strdup("SET PLAYER");
    buttons[1].texture = get_text_surface(all, "SET PLAYER", buttons[1].dstrect, BLACK);
    buttons[2].dstrect = (SDL_Rect){50, 450, 50, 50};
    buttons[2].title = ft_strdup(" - ");
    buttons[2].texture = get_text_surface(all, " - ", buttons[2].dstrect, BLACK);
    buttons[3].dstrect = (SDL_Rect){250, 450, 50, 50};
    buttons[3].title = ft_strdup(" + ");
    buttons[3].texture = get_text_surface(all, " + ", buttons[3].dstrect, BLACK);
    // buttons[4].dstrect = (SDL_Rect){105, 450, 50, 140};
    // buttons[4].title = ft_strdup(" 0 ");
    // buttons[4].texture = get_text_surface(all, " 0 ", buttons[4].dstrect, BLACK);

    i = 0;
    while(i < 4)
    {
        buttons[i].color = WHITE;
        buttons[i++].state = 0;
    }
    return (1);
}

int             load_texture(t_all *all)
{
    if(!(all->texture = get_texture("plain.bmp", all->sdl)))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(all->player.picture = get_texture("player.bmp", all->sdl)))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(load_buttons(all, all->buttons) == 1))
        error_and_close(__FILE__, __FUNCTION__);
    return (0);
}