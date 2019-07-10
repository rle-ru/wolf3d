/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:04:29 by dacuvill          #+#    #+#             */
/*   Updated: 2019/07/10 10:45:03 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <math.h>
#include <SDL.h>

static void		check_ray_direction(t_wolf *w, double raydirx, double raydiry)
{
	if (raydirx < 0)
	{
		w->player.step.x = -1;
		w->player.sidedist.x = (w->player.pos.x - w->player.map.x)
			* w->player.deltadist.x;
	}
	else
	{
		w->player.step.x = 1;
		w->player.sidedist.x = (w->player.map.x + 1.0 - w->player.pos.x)
			* w->player.deltadist.x;
	}
	if (raydiry < 0)
	{
		w->player.step.y = -1;
		w->player.sidedist.y = (w->player.pos.y - w->player.map.y)
			* w->player.deltadist.y;
	}
	else
	{
		w->player.step.y = 1;
		w->player.sidedist.y = (w->player.map.y + 1.0 - w->player.pos.y)
			* w->player.deltadist.y;
	}
}

static int		check_collision(t_wolf *w, int *side)
{
	int		hit;

	hit = 0;
	while (!hit)
	{
		if (w->player.sidedist.x < w->player.sidedist.y)
		{
			w->player.sidedist.x += w->player.deltadist.x;
			w->player.map.x += w->player.step.x;
			*side = 0;
		}
		else
		{
			w->player.sidedist.y += w->player.deltadist.y;
			w->player.map.y += w->player.step.y;
			*side = 1;
		}
		if (w->map[w->player.map.x][w->player.map.y] > 0)
			hit = 1;
	}
	return (w->map[w->player.map.x][w->player.map.y]);
}

static void		put_line(t_wolf *w, int x, int xd, int text)
{
	int			y;
	int			i;
	int			*pixels;
	SDL_Surface	*t;
	double		prog;

	t = w->text[text];
	pixels = (int*)(w->text[text]->pixels);
	i = w->ray.draw_start * W_WIDTH + x;
	y = w->ray.draw_start;
	while (y < w->ray.draw_end)
	{
		prog = (double)((double)(y - w->ray.yts)
			/ (double)(w->ray.yte - w->ray.yts));
		w->canvas.img[i] = pixels[(int)(((int)(prog * t->h)) * t->w) + xd];
		i += W_WIDTH;
		++y;
	}
}

static void		ray_casting2(t_wolf *w, int side, int x, int text)
{
	double	dx;

	if (!side)
		w->player.pwdist = (w->player.map.x - w->player.pos.x
			+ (1 - w->player.step.x) * 0.5) / w->ray.raydirx;
	else
		w->player.pwdist = (w->player.map.y - w->player.pos.y
			+ (1 - w->player.step.y) * 0.5) / w->ray.raydiry;
	w->ray.line_heigth = (int)(W_GHEIGHT / w->player.pwdist);
	w->ray.draw_start = -(w->ray.line_heigth) * 0.5 + W_GHEIGHT2;
	w->ray.yts = w->ray.draw_start;
	if (w->ray.draw_start < 0)
		w->ray.draw_start = 0;
	w->ray.draw_end = w->ray.line_heigth * 0.5 + W_GHEIGHT2;
	w->ray.yte = w->ray.draw_end;
	if (w->ray.draw_end >= W_GHEIGHT)
		w->ray.draw_end = W_GHEIGHT - 1;
	if (side == 0)
		dx = w->player.pos.y + w->player.pwdist * w->ray.raydiry;
	else
		dx = w->player.pos.x + w->player.pwdist * w->ray.raydirx;
	dx -= (int)dx;
	put_line(w, x, (int)(dx * w->text[0]->w), text);
}

int				ray_casting(t_wolf *w)
{
	double	camx;
	int		x;
	int		side;
	int		text;

	x = 0;
	while (x < W_WIDTH)
	{
		camx = 2 * x / (double)W_WIDTH - 1;
		w->ray.raydirx = w->player.dir.x + w->player.plane.x * camx;
		w->ray.raydiry = w->player.dir.y + w->player.plane.y * camx;
		w->player.map.x = (int)w->player.pos.x;
		w->player.map.y = (int)w->player.pos.y;
		w->player.deltadist.x = sqrt(1 + (w->ray.raydiry * w->ray.raydiry)
			/ (w->ray.raydirx * w->ray.raydirx));
		w->player.deltadist.y = sqrt(1 + (w->ray.raydirx * w->ray.raydirx)
			/ (w->ray.raydiry * w->ray.raydiry));
		check_ray_direction(w, w->ray.raydirx, w->ray.raydiry);
		text = check_collision(w, &side);
		ray_casting2(w, side, x, text);
		++x;
	}
	return (0);
}
