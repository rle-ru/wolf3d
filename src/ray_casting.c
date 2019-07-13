/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:04:29 by dacuvill          #+#    #+#             */
/*   Updated: 2019/07/13 14:25:34 by rle-ru           ###   ########.fr       */
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
			*side = ((w->player.pos.x < w->player.map.x) ? 0 : 2);
		}
		else
		{
			w->player.sidedist.y += w->player.deltadist.y;
			w->player.map.y += w->player.step.y;
			*side = ((w->player.pos.y < w->player.map.y) ? 1 : 3);
		}
		if (w->player.map.x < 0 || w->player.map.x >= w->width
			|| w->player.map.y < 0 || w->player.map.y >= w->hei)
			return (INT_MIN);
		if (w->map[w->player.map.x][w->player.map.y] > 0)
			hit = 1;
	}
	return (w->map[w->player.map.x][w->player.map.y]);
}

void			put_line(t_wolf *w, int x, int xd, int text)
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

int				ray_casting(t_wolf *w)
{
	double	camx;
	int		x;
	int		side;
	int		text;

	x = 0;
	while (x < W_WIDTH)
	{
		camx = (2 * x / (double)W_WIDTH - 1) * (W_WIDTH / W_GHEIGHT);
		w->ray.raydirx = -w->player.dir.x + w->player.plane.x * camx;
		w->ray.raydiry = -w->player.dir.y + w->player.plane.y * camx;
		w->player.map.x = (int)w->player.pos.x;
		w->player.map.y = (int)w->player.pos.y;
		w->player.deltadist.x = sqrt(1 + (w->ray.raydiry * w->ray.raydiry)
			/ (w->ray.raydirx * w->ray.raydirx));
		w->player.deltadist.y = sqrt(1 + (w->ray.raydirx * w->ray.raydirx)
			/ (w->ray.raydiry * w->ray.raydiry));
		check_ray_direction(w, w->ray.raydirx, w->ray.raydiry);
		++x;
		if ((text = check_collision(w, &side)) != INT_MIN)
			ray_casting2(w, side, x - 1, text);
	}
	return (0);
}
