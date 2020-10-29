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
# define PICT_WIDTH 90
// # define OBJECTS (MAP_HEIGHT * MAP_WIDTH)
# define BUTTONS 10
# define OBJ_SIDE 57
// # define LAYER 2
# define EYE_HEIGHT 6

typedef	struct		s_color
{
	int				r;
	int				g;
	int				b;
	int				a;
}					t_color;

typedef struct	    s_sdl
{
	SDL_Window	    *window;
	SDL_Renderer	*renderer;
}				    t_sdl;

typedef struct      s_xyint
{
    int           x;
    int           y;
}                   t_xyint;

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
	float		floor;
	float		ceil;
	t_xy		*vertex;		//	Координаты всех вершин данного сектора, причем первая координаты дублируется в конце
	int		 *neighbors;		//	Номера всех соседей данного сектора
	unsigned	npoints; //	Количество соседей
			
}                   t_sect;

typedef struct      s_object
{
    t_sect			*sector;
	// SDL_Texture		*texture;
	SDL_Surface		*texture;

    SDL_Rect        dstrect;
}                   t_object;

typedef struct      s_button
{
    t_object        object;
    int             state;
}                   t_button;

typedef struct      s_edit
{
    int             function;
	t_xyz			coord;
	t_sect			new_sector;
}                   t_edit;

typedef	struct	s_player
{
	t_xyz		where;			//	Current position
	t_xyz		velocity;
	// SDL_Texture	*picture;
	SDL_Surface	*picture;

	int			picked;		//	Current motion vector
	// float		angle;			//	Looking towards
	// float		anglesin;		//	and sin()
	// float		anglecos;		//	and cos()
	// float		temp_yaw;		//TODO WTF
	// float		yaw;			//	and player angle when looking up and down
	// unsigned	sector;
	// int			wsad[4];
	// float		move_vec[2];
	// int			ground;
	// int			falling;
	// int			moving;
	// int			ducking;
	// int			pushing;
	// float		acceleration;
	// float		eyeheight;
	// SDL_Event	event;
}				t_player;

typedef struct      s_all
{
    t_player        player;// переменная игрока. 
    t_sect          *swap;//указатель на выбранный сектор
    t_sect          *sectors;//массив с данными о секторах
	t_sect			*temp;			
    unsigned int    num_sectors;//количество секторов
	int 			step;//шаг (масштаб)
	int 			iso;
	// float			angle;//угол поворота
	// t_xyz			rot;//
	t_xyint			point;//координаты ближайшей точки курсора
    t_xyz			mouse;//координаты мыши на area
	t_xyz			mapsize;//размер карты в исходной СИ
	t_xy			min_coord;
	t_xy			max_coord;
    SDL_Rect        area;//область редактирования
    // SDL_Texture     *texture;//текстура-подложка 
    SDL_Surface     *texture;//текстура-подложка 

    t_object        map[690][876];//массив пикселей области  area
	// t_xyz			map_whl;//
    t_button        buttons[BUTTONS];//кнопки
    t_edit			edit;//
    t_sdl           *sdl;//
}                   t_all;

t_all               *init_all(); // инициализируем модули
void                error_and_close(const char *file, const char *function); // аварийное завершение программы
void                on_event(t_all *all, SDL_Event *event); //обработка событий
void				map_click(t_xyz *mouse, t_sect *sector, t_all *all);
int					load_map(char *name, t_all *all); // загрузка карты
int                 load_texture(t_all *all);// звгрузка текстур
void                draw_all(t_all *all, SDL_Renderer *rnd, t_button *btn);//отрисовка
int					write_map(char *name, t_all *all);
void				draw_player(t_all *all, SDL_Renderer *rnd, t_player *player, t_xy *c);
void				draw_grid(t_all *all, SDL_Rect *area, int step);
void    			draw_texture(SDL_Renderer *rnd, SDL_Rect area, SDL_Surface *txt);
void    			draw_fill_rect(t_all *all, SDL_Rect area, t_color *color);
void				draw_line(t_all *all, t_xyz *start, t_xyz *fin);
void				draw_circle(SDL_Renderer *rnd, int x, int y, int r);

# endif