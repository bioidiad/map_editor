#include "editor.h"

void	draw_line(t_all *all, t_xyz *start, t_xyz *fin)
{
	float		dx;
	float		dy;
	int	l;
	int i;
	float x, y;

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
			angle = (2 * 3.14 * i) / 50;
			dx = r * cosf(angle);
			dy = r * sinf(angle);
			SDL_RenderDrawPoint(rnd, x + dx, y + dy);
		}
	}
}

void    draw_fill_rect(t_all *all, SDL_Rect area, t_color *color)
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