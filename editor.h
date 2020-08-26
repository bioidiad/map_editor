#ifndef EDITOR_H
# define EDITOR_H


# include <SDL2/SDL.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

# define MAP_WIDTH 11
# define MAP_HEIGHT 11
# define MAP_ELEMENTS 4
# define WIDTH 864
# define HEIGHT 632
# define FPS 24
# define PICT_HEIGHT 50
# define PICT_WIDTH 50
// # define OBJECTS (MAP_HEIGHT * MAP_WIDTH)
# define BUTTONS 10
# define OBJ_SIDE 57
# define LAYER 2

typedef struct	    s_sdl
{
	SDL_Window	    *window;
	SDL_Renderer	*renderer;
}				    t_sdl;

typedef struct      s_object
{
    SDL_Texture     *texture;
    SDL_Rect        dstrect;
}                   t_object;

typedef struct      s_button
{
    t_object        object;
    int             state;
    SDL_Texture     *swap;
}                   t_button;

typedef struct      s_line
{
    int             state;
    int             x1;
    int             y1;
    int             x2;
    int             y2;
}                   t_line;

typedef struct      s_all
{
    int             layer;
    char            *map;
    t_line          line;
    SDL_Rect        area;
    SDL_Texture     *texture;
    t_object        object[LAYER][MAP_WIDTH][MAP_HEIGHT];
    t_button        buttons[BUTTONS];
    
    t_sdl           *sdl;
}                   t_all;

t_all               *init_all(); // инициализируем модули
void                error_and_close(const char *file, const char *function); // аварийное завершение программы
void                on_event(t_all *all, SDL_Event *event); //обработка событий

int                 load_texture(char *file, t_all *all);// звгрузка текстур
void                draw_all(t_all *all, SDL_Renderer *rnd, t_button *btn);//отрисовка

# endif