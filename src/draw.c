/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:02:05 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/22 15:14:43 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "wolf3d.h"
#include "libft.h"

int			ray_casting(t_wolf *w)
{
	int		x;
	double	camx;
	double	raydirx;
	double	raydiry;
	double	planex;
	double	planey;

	planex = 0;
	planey = 0.66;
	x = 0;
	while (x < W_WIDTH)
	{
		camx = 2 * x / (double)W_WIDTH - 1;
		raydirx = w->player.dir.x + planex * camx;
		raydiry = w->player.dir.y + planey * camx;
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
