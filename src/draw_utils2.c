#include "editor.h"

void	draw_player(t_all *all, SDL_Renderer *rnd, t_player *player, t_xy *c)
{
	SDL_Rect loc;

	if (all->player.picked == 0)
	//(temp->vertex[j].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step)
		loc = (SDL_Rect){(player->where.x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step),
		 (player->where.y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step),
	 		 all->step, all->step};
	else if (all->player.picked == 1)
		loc = (SDL_Rect){all->point.x * all->step + c->x, all->point.y * all->step + c->y, all->step, all->step};
	draw_texture(rnd, loc, player->picture);

	// SDL_RenderCopy(rnd, player->picture, NULL, &loc);
}

void	draw_grid(t_all *all, SDL_Rect *area, int step)
{
	t_xy	c;

	c = (t_xy){(area->w / 2) % step, (area->h / 2) % step};
	SDL_SetRenderDrawColor(all->sdl->renderer, 255, 255, 255, 70);
	while (c.x <= area->w)
	{
		draw_line(all, &(t_xyz){c.x, 0, 0}, &(t_xyz){c.x, area->h});
		c.x += step;
	}
	c.x = 0;
	while (c.y <= area->h)
	{
		draw_line(all, &(t_xyz){c.x, c.y, 0}, &(t_xyz){area->w, c.y});
		c.y += step;
	}
}