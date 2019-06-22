/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 09:21:56 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/22 11:20:03 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "wolf3d.h"

t_error	init_mlx(t_wolf *w)
{
	if (!(w->canvas.mlx_ptr = mlx_init()))
		return (falloc);
	if (!(w->canvas.window = mlx_new_window(w->canvas.mlx_ptr,
		W_WIDTH, W_HEIGHT, "Wolfenstein 3D")))
		return (falloc);
	if (!(w->canvas.img.img_ptr = mlx_new_image(w->canvas.mlx_ptr,
		W_WIDTH, W_HEIGHT)))
		return (falloc);
	if (!(w->canvas.img.img = (int*)mlx_get_data_addr(w->canvas.img.img_ptr,
			&w->canvas.img.bpp, &w->canvas.img.stride, &w->canvas.img.endian)))
		return (falloc);
	mlx_hook(w->canvas.window, 2, 1, key_hook, w);
	mlx_hook(w->canvas.window, 17, 0, hook_leave, w);
	mlx_hook(w->canvas.window, 3, 1, key_unhook, w);
	// mlx_hook(fra->canvas.window, 4, 1, mouse_hook, fra);
	// mlx_hook(fra->canvas.window, 5, 1, mouse_unhook, fra);
	// mlx_hook(fra->canvas.window, 6, 6, mouse_notify, fra);
	mlx_loop_hook(w->canvas.mlx_ptr, draw, w);
	mlx_loop(w->canvas.mlx_ptr);
	return (ok);
}
