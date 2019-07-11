/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:04:29 by dacuvill          #+#    #+#             */
/*   Updated: 2019/07/11 15:10:30 by rle-ru           ###   ########.fr       */
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
		if (w->player.map.x < 0 || w->player.map.x >= w->width || w->player.map.y < 0 || w->player.map.y >= w->height)
			return (INT_MIN);
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
	double	fxw;
	double	fyw;

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
	put_line(w, x, (int)(dx * w->text[text]->w), text);
	if (side == 0 && w->ray.raydirx > 0)
	{
		fxw = w->player.map.x;
		fyw = w->player.map.y + dx;
	}
	else if (side == 0 && w->ray.raydirx < 0)
	{
		fxw = w->player.map.x + 1.0;
		fyw = w->player.map.y + dx;
	}
	else if (side == 1 && w->ray.raydiry > 0)
	{
		fxw = w->player.map.x + dx;
		fyw = w->player.map.y;
	}
	else
	{
		fxw = w->player.map.x + dx;
		fyw = w->player.map.y + 1.0;
	}
	if (w->player.map.x < 0 || w->player.map.x >= w->width || w->player.map.y < 0 || w->player.map.y >= w->height)
	{
		++x;
		return ;
	}
	
	
	double	dw;
	double	dp;
	double	cd;
	double	cfx;
	double	cfy;
	double	weight;
	int		y;
	int		ftx;
	int		fty;

	dw = w->player.pwdist;
	dp = 0.0;
	if (w->ray.draw_end < 0)
		w->ray.draw_end = W_GHEIGHT;
	y = w->ray.draw_end + 1;
	while (y < W_GHEIGHT)
	{
		cd = W_GHEIGHT / (2.0 * y - W_GHEIGHT);
		weight = (cd - dp) / (dw - dp);
		cfx = weight * fxw + (1.0 - weight) * w->player.pos.x;
		cfy = weight * fyw + (1.0 - weight) * w->player.pos.y;
		ftx = (int)(cfx * w->text[0]->w) % w->text[0]->w;
		fty = (int)(cfy * w->text[0]->h) % w->text[0]->h;
		w->canvas.img[(int)(y * W_WIDTH + x)] = ((int*)(w->text[0]->pixels))[fty * w->text[0]->w + ftx];
		ftx = (int)(cfx * w->text[7]->w) % w->text[7]->w;
		fty = (int)(cfy * w->text[7]->h) % w->text[7]->h;
		w->canvas.img[(int)((W_GHEIGHT - y) * W_WIDTH + x)] = ((int*)(w->text[7]->pixels))[fty * w->text[7]->w + ftx];
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
		w->ray.raydirx = w->player.dir.x + w->player.plane.x * camx;
		w->ray.raydiry = w->player.dir.y + w->player.plane.y * camx;
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
