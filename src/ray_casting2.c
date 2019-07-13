/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 10:52:53 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/13 11:25:57 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <SDL.h>

static void	floor_ceil(t_wolf *w, int x)
{
	int			y;
	t_ray_cast	r;

	r = w->ray;
	r.dw = w->player.pwdist;
	r.dp = 0.0;
	if (r.draw_end < 0)
		w->ray.draw_end = W_GHEIGHT;
	y = w->ray.draw_end + 1;
	while (y < W_GHEIGHT)
	{
		r.cd = W_GHEIGHT / (2.0 * y - W_GHEIGHT);
		r.weight = (r.cd - r.dp) / (r.dw - r.dp);
		r.cfx = r.weight * w->ray.fxw + (1.0 - r.weight) * w->player.pos.x;
		r.cfy = r.weight * w->ray.fyw + (1.0 - r.weight) * w->player.pos.y;
		r.ftx = (int)(r.cfx * w->text[0]->w) % w->text[0]->w;
		r.fty = (int)(r.cfy * w->text[0]->h) % w->text[0]->h;
		w->canvas.img[(int)(y * W_WIDTH + x)] = ((int*)(w->text[0]->pixels))
			[r.fty * w->text[0]->w + r.ftx];
		r.ftx = (int)(r.cfx * w->text[6]->w) % w->text[6]->w;
		r.fty = (int)(r.cfy * w->text[6]->h) % w->text[6]->h;
		w->canvas.img[(int)((W_GHEIGHT - y) * W_WIDTH + x)] =
			((int*)(w->text[6]->pixels))[r.fty * w->text[6]->w + r.ftx];
		++y;
	}
}

static void	init_fc(t_wolf *w, double dx, int side)
{
	if (side % 2 == 0 && w->ray.raydirx > 0)
	{
		w->ray.fxw = w->player.map.x;
		w->ray.fyw = w->player.map.y + dx;
	}
	else if (side % 2 == 0 && w->ray.raydirx < 0)
	{
		w->ray.fxw = w->player.map.x + 1.0;
		w->ray.fyw = w->player.map.y + dx;
	}
	else if (side % 2 == 1 && w->ray.raydiry > 0)
	{
		w->ray.fxw = w->player.map.x + dx;
		w->ray.fyw = w->player.map.y;
	}
	else
	{
		w->ray.fxw = w->player.map.x + dx;
		w->ray.fyw = w->player.map.y + 1.0;
	}
}

void		init_ray2(t_wolf *w, int side)
{
	if (!(side % 2))
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
}

void		ray_casting2(t_wolf *w, int side, int x, int text)
{
	double	dx;
	int		text2;

	init_ray2(w, side);
	if (w->ray.draw_end >= W_GHEIGHT)
		w->ray.draw_end = W_GHEIGHT;
	if (side % 2 == 0)
		dx = w->player.pos.y + w->player.pwdist * w->ray.raydiry;
	else
		dx = w->player.pos.x + w->player.pwdist * w->ray.raydirx;
	dx -= (int)dx;
	text2 = (((text + side) > TEXTURES_N - 1) ? (TEXTURES_N - 1) :
		(text + side));
	put_line(w, x, (int)(dx * w->text[text2]->w), text2);
	init_fc(w, dx, side);
	if (w->player.map.x < 0 || w->player.map.x >= w->width
		|| w->player.map.y < 0 || w->player.map.y >= w->hei)
	{
		++x;
		return ;
	}
	floor_ceil(w, x);
}
