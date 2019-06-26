/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:02:05 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/26 12:07:33 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "wolf3d.h"
#include "libft.h"
#include <math.h>

int			ray_casting(t_wolf *w)
{
	int		x;
	double	camx;
	double	raydirx;
	double	raydiry;
	int		hit;
	int		side;

	x = 0;
	while (x < W_WIDTH)
	{
		camx = 2 * x / (double)W_WIDTH - 1;
		raydirx = w->player.dir.x + w->player.plane.x * camx;
		raydiry = w->player.dir.y + w->player.plane.y * camx;
		w->player.map.x = (int)w->player.pos.x;
		w->player.map.y = (int)w->player.pos.y;
		w->player.deltadist.x = sqrt(1 + (raydiry * raydiry) / (raydirx * raydirx));
		w->player.deltadist.y = sqrt(1 + (raydirx * raydirx) / (raydiry * raydiry));
		hit = 0;
		if (raydirx < 0)
		{
			w->player.step.x = -1;
			w->player.sidedist.x = (w->player.pos.x - w->player.map.x) * w->player.deltadist.x;
		}
		else
		{
			w->player.step.x = 1;
			w->player.sidedist.x = (w->player.map.x + 1.0 - w->player.pos.x) * w->player.deltadist.x;
		}
		if (raydiry < 0)
		{
			w->player.step.y = -1;
			w->player.sidedist.y = (w->player.pos.y - w->player.map.y) * w->player.deltadist.y;
		}
		else
		{
			w->player.step.y = 1;
			w->player.sidedist.y = (w->player.map.y + 1.0 - w->player.pos.y) * w->player.deltadist.y;
		}
		while (!hit)
		{
			if (w->player.sidedist.x < w->player.sidedist.y)
			{
				w->player.sidedist.x += w->player.deltadist.x;
				w->player.map.x += w->player.step.x;
				side = 0;
			}
			else
			{
				w->player.sidedist.y += w->player.deltadist.y;
				w->player.map.y += w->player.step.y;
				side = 1;
			}
			if (w->map[w->player.map.y * w->width + w->player.map.x] > 0)
				hit = 1;
		}
		if (!side)
			w->player.pwdist = (w->player.map.x - w->player.pos.x + (1 - w->player.step.x) * 0.5) / raydirx;
		else
			w->player.pwdist = (w->player.map.y - w->player.pos.y + (1 - w->player.step.y) * 0.5) / raydiry;
		int lineh = (int)(W_HEIGHT / w->player.pwdist);
		int draws = -lineh * 0.5 + W_HEIGHT * 0.5;
		if (draws < 0)
			draws = 0;
		int drawe = lineh * 0.5 + W_HEIGHT * 0.5;
		if (drawe >= W_HEIGHT)
			drawe = W_HEIGHT - 1;
		bresenham(w, (t_point){x, draws}, (t_point){x, drawe});
		++x;
	}
	return (0);
}

int			draw(t_wolf *w)
{
	mlx_clear_window(w->canvas.mlx_ptr, w->canvas.window);
	ft_bzero(w->canvas.img.img, W_WIDTH * W_HEIGHT * sizeof(int));
	ray_casting(w);//
	mlx_put_image_to_window(w->canvas.mlx_ptr, w->canvas.window,
		w->canvas.img.img_ptr, 0, 0);
	return (0);
}
