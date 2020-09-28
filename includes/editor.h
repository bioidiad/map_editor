#ifndef EDITOR_H
# define EDITOR_H


# include "../SDL/SDL.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

# define MAP_WIDTH 11
# define MAP_HEIGHT 11
# define MAP_ELEMENTS 4
# define WIDTH 1200
# define HEIGHT 700
# define FPS 200
# define PICT_HEIGHT 50
# define PICT_WIDTH 50
// # define OBJECTS (MAP_HEIGHT * MAP_WIDTH)
# define BUTTONS 10
# define OBJ_SIDE 57
// # define LAYER 2
# define EYE_HEIGHT 6

typedef struct	    s_sdl
{
	SDL_Window	    *window;
	SDL_Renderer	*renderer;
}				    t_sdl;

typedef struct      s_xy
{
    float           x;
    float           y;
}                   t_xy;

typedef struct	s_xyz
{
	float		x;
	float		y;
	float		z;
}				t_xyz;

typedef struct      s_sect
{
	int			select;
	float		floor;
	float		ceil;
	t_xy		*vertex;		//	Координаты всех вершин данного сектора, причем первая координаты дублируется в конце
	signed char *neighbors;		//	Номера всех соседей данного сектора
	unsigned	npoints; //	Количество соседей
			
}                   t_sect;

typedef struct      s_object
{
    t_sect			*sector;
	SDL_Texture		*texture;
    SDL_Rect        dstrect;
}                   t_object;

typedef struct      s_button
{
    t_object        object;
    int             state;
    SDL_Texture     *swap;
}                   t_button;

// typedef struct      s_line
// {
//     int             state;
//     int             x1;
//     int             y1;
//     int             x2;
//     int             y2;
// }                   t_line;

typedef	struct	s_player
{
	t_xyz		where;			//	Current position
	t_xyz		velocity;		//	Current motion vector
	float		angle;			//	Looking towards
	float		anglesin;		//	and sin()
	float		anglecos;		//	and cos()
	float		temp_yaw;		//TODO WTF
	float		yaw;			//	and player angle when looking up and down
	unsigned	sector;
	int			wsad[4];
	float		move_vec[2];
	int			ground;
	int			falling;
	int			moving;
	int			ducking;
	int			pushing;
	float		acceleration;
	float		eyeheight;
	SDL_Event	event;
}				t_player;

typedef struct      s_all
{
    t_player        player;
    // int             layer;
    t_sect          *sectors;
    unsigned int    num_sectors;
	int 			step;
	float			angle;
	t_xyz			rot;
    t_xyz			mouse;
	t_xyz			mapsize;
    SDL_Rect        area;
    SDL_Texture     *texture;
    t_object        map[690][876];
    t_button        buttons[BUTTONS];
    
    t_sdl           *sdl;
}                   t_all;

t_all               *init_all(); // инициализируем модули
void                error_and_close(const char *file, const char *function); // аварийное завершение программы
void                on_event(t_all *all, SDL_Event *event); //обработка событий
void				load_map(t_all *all); // загрузка карты
int                 load_texture(char *file, t_all *all);// звгрузка текстур
void                draw_all(t_all *all, SDL_Renderer *rnd, t_button *btn);//отрисовка

# endif