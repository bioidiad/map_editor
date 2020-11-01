#include "editor.h"

void	draw_line(t_all *all, t_xyz *start, t_xyz *fin, SDL_Color color)
{
	float		dx;
	float		dy;
	int	l;
	int i;
	float x, y;

	SDL_SetRenderDrawColor(all->sdl->renderer, color.r, color.g, color.b, color.a);

	l = (int)fmax(abs((int)start->x - (int)fin->x), abs((int)start->y - (int)fin->y));
	dx = (fin->x - start->x) / l;
	dy = (fin->y - start->y) / l;
	x = (int)(start->x);
	y = (int)(start->y); 
	i = 0;

	while (i < l)
	{
		x = x + dx;
		y = y + dy;
		i++;
		SDL_RenderDrawPoint(all->sdl->renderer, (int)x, (int)y);
		// if (x > 1 && y > 1 && x < all->area.w && y < all->area.h - 1)
		// {
		// 	all->map[(int)y][(int)x].sector = sect;
		// 	all->map[(int)y + 1][(int)x + 1].sector = sect;
		// 	all->map[(int)y - 1][(int)x - 1].sector = sect;//записываем вершины по координатам пикселей
		// //printf("sectx = %f:%f\n", all->map[(int)y][(int)x].sector->vertex->x, sect->vertex->y);
		// }
	} 	
}

void	draw_circle(SDL_Renderer *rnd, int x, int y, int r)
{
	int 	i;
	float	angle;
	float dx;
	float dy;
	int f;
	//printf("x:y = %d : %d\n", x, y);
	
	f = 0;
	while (f++ <= r)
	{
		i = 0;
		while (i++ < 50)
		{
			angle = (2 * M_PI * i) / 50;
			dx = r * cosf(angle);
			dy = r * sinf(angle);
			SDL_RenderDrawPoint(rnd, x + dx, y + dy);
		}
	}
}

void    draw_fill_rect(t_all *all, SDL_Rect area, SDL_Color *color)
{
    int x;
    int y;

    SDL_SetRenderDrawColor(all->sdl->renderer, color->r, color->g, color->b, color->a);
    x = area.x;
    while (x < area.x + area.w)
    {
        y = area.y;
        while(y < area.y + area.h)
        {
            SDL_RenderDrawPoint(all->sdl->renderer, x, y);
            y++;
        }
        x++;
    }
}

Uint32		get_pixel_color(SDL_Surface *surface, const int x,\
									const int y)
{
	Uint8	*p;
	Uint32	rgb;

	p = (Uint8 *)surface->pixels + y * surface->pitch + x
			* surface->format->BytesPerPixel;
	rgb = p[3] << 24 | p[2] << 16 | p[1] << 8 | p[0];
	return (rgb);
}

void    draw_texture(SDL_Renderer *rnd, SDL_Rect area, SDL_Surface *txt)
{
    float x;
    float y;
    Uint32 col;
	float kx, ky;
	
	kx = (float)txt->w / area.w;
	ky = (float)txt->h / area.h;
	
    y = 0;
    while(y < area.h)
    {
        x = 0;
        while(x < area.w)
        {
            col = get_pixel_color(txt,kx*x, ky*y);
            SDL_SetRenderDrawColor(rnd, col >> 16, col >> 8, col, 255);
			if(col >> 24 != 0)
            	SDL_RenderDrawPoint(rnd, area.x + x, area.y + y);
			x++;
        }
		y++;
    }
}