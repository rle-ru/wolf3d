/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:09:08 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/02 13:36:11 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>

void	ft_init_fdf(t_fdf *fdf)
{
	fdf->f[0].f = &bresenham;
	fdf->f[1].f = &xiaolin;
	fdf->relief = 0.1;
	fdf->canvas.mlx_ptr = mlx_init();
	fdf->canvas.window = mlx_new_window(fdf->canvas.mlx_ptr,
		fdf->canvas.w_width, fdf->canvas.w_height, "fdf");
	fdf->cam.pos.z = (fdf->width > fdf->height ? fdf->width : fdf->height) * -1;
	fdf->cam.pos.x = fdf->width >> 3;
	fdf->cam.pos.y = fdf->height >> 3;
	fdf->cam.rot_angles.z = -M_PI;
	fdf->cam.pre_rot_angles = (t_vector3){-1000, -1000, -1000, 0};
	if (!(fdf->canvas.img.img_ptr = mlx_new_image(fdf->canvas.mlx_ptr,
		(int)fdf->canvas.w_width, (int)fdf->canvas.w_height)))
		ft_leave(falloc, fdf);
	if (!(fdf->canvas.img.img =
		(int*)mlx_get_data_addr(fdf->canvas.img.img_ptr, &fdf->canvas.img.bpp,
		&fdf->canvas.img.stride, &fdf->canvas.img.endian)))
		ft_leave(falloc, fdf);
	fdf->speed = 0.1 * (fdf->height > 500 ? 500 : fdf->height) / 5;
	init_matrixes(fdf);
	mlx_hook(fdf->canvas.window, 2, 1, key_hook, fdf);
	mlx_hook(fdf->canvas.window, 17, 0, hook_leave, fdf);
	mlx_loop_hook(fdf->canvas.mlx_ptr, draw_map, fdf);
	mlx_loop(fdf->canvas.mlx_ptr);
}
