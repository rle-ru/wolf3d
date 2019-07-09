/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:04:29 by dacuvill          #+#    #+#             */
/*   Updated: 2019/07/09 12:16:18 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <math.h>
#include <SDL.h>

int				choose_color(int tile)
{
	if (tile == 1)
		return (0xFFF0);
	else if (tile == 2)
		return (0xFFF);
	else if (tile == 3)
		return (0xFF);
	else
		return (0xFFFFFF);
}

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

static void		check_collision(t_wolf *w, int *side)
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
}

static void		put_line(t_wolf *w, int x, double xd)
{
	int	y;
	int	i;
	int	yt;

	i = w->ray.draw_start * W_WIDTH + x;
	y = w->ray.draw_start;
	while (y < w->ray.draw_end)
	{
		yt = (int)();
		w->canvas.img[i] = w->text->pixels[yt * w->text->w + 0];//
		i += W_WIDTH;
		++y;
	}
}

static void		ray_casting2(t_wolf *w, int side, int x)
{
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
	put_line(w, x);//
	w->ray.color = choose_color(w->map[w->player.map.x][w->player.map.y]);
	// bresenham(w, (t_point){x, w->ray.draw_start}, (t_point){x, w->ray.draw_end},
		// side == 1 ? w->ray.color : (w->ray.color >> 1));
	//remplacer bresenham par une fonction qui dessine en vertical, sans multiplication
}

int				ray_casting(t_wolf *w)
{
	double	camx;
	int		x;
	int		side;

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
		check_collision(w, &side);
		ray_casting2(w, side, x);
		++x;
	}
	return (0);
}
