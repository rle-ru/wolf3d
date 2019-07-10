/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 09:21:56 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/10 14:03:20 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <SDL.h>
#include <SDL_image.h>

t_error	init_textures(t_wolf *w)
{
	if (!(w->text[0] = SDL_ConvertSurfaceFormat(IMG_Load("pics/colorstone.png"), SDL_PIXELFORMAT_ARGB8888, 0)))
		return (falloc);
	if (!(w->text[1] = SDL_ConvertSurfaceFormat(IMG_Load("pics/eagle.png"), SDL_PIXELFORMAT_ARGB8888, 0)))
		return (falloc);
	if (!(w->text[2] = SDL_ConvertSurfaceFormat(IMG_Load("pics/greystone.png"), SDL_PIXELFORMAT_ARGB8888, 0)))
		return (falloc);
	if (!(w->text[3] = SDL_ConvertSurfaceFormat(IMG_Load("pics/mossy.png"), SDL_PIXELFORMAT_ARGB8888, 0)))
		return (falloc);
	if (!(w->text[4] = SDL_ConvertSurfaceFormat(IMG_Load("pics/redbrick.png"), SDL_PIXELFORMAT_ARGB8888, 0)))
		return (falloc);
	if (!(w->text[5] = SDL_ConvertSurfaceFormat(IMG_Load("pics/purplestone.png"), SDL_PIXELFORMAT_ARGB8888, 0)))
		return (falloc);
	if (!(w->text[6] = SDL_ConvertSurfaceFormat(IMG_Load("pics/wood.png"), SDL_PIXELFORMAT_ARGB8888, 0)))
		return (falloc);
	if (!(w->text[7] = SDL_ConvertSurfaceFormat(IMG_Load("pics/jesuc.jpg"), SDL_PIXELFORMAT_ARGB8888, 0)))
		return (falloc);
	return (ok);
}

t_error	init_sdl(t_wolf *w)
{

	if (init_textures(w) != ok)
		return (falloc);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (falloc);
	w->canvas.window = SDL_CreateWindow(
					"Wolfenstein 3D",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					W_WIDTH,
					W_HEIGHT,
					SDL_WINDOW_SHOWN);
		// return (falloc);
	w->canvas.renderer = SDL_CreateRenderer(w->canvas.window, -1,
			SDL_RENDERER_ACCELERATED);
		// return (falloc);
	SDL_RenderSetLogicalSize(w->canvas.renderer, W_WIDTH, W_HEIGHT);
	if (!(w->canvas.texture = SDL_CreateTexture(w->canvas.renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		W_WIDTH, W_HEIGHT)))
		return (falloc);
	if (!(w->canvas.img = malloc(IMG_SIZE)))
		return (falloc);
	// SDL_SetRelativeMouseMode(SDL_TRUE); //No mouse
	// SDL_SetWindowGrab(w->canvas.window, SDL_TRUE);// Mouse locked in window
	
	
	
	// SDL_Delay(3000);
	// SDL_DestroyWindow(w->canvas.window);
	// SDL_Quit();


	// if (!(w->canvas.renderer = SDL_CreateRenderer(w->canvas.window, -1,
	// 		SDL_RENDERER_ACCELERATED)))
	// 	return (falloc);
	// if (!(w->canvas.screen = SDL_CreateTexture(w->canvas.renderer,
	// 	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
	// 	W_WIDTH, W_HEIGHT)))
	// 	return (falloc);
	// SDL_SetWindowGrab(w->canvas.window, SDL_TRUE);
	// if (!(w->canvas.mlx_ptr = mlx_init()))
	// 	return (falloc);
	// if (!(w->canvas.window = mlx_new_window(w->canvas.mlx_ptr,
	// 	W_WIDTH, W_HEIGHT, "Wolfenstein 3D")))
	// 	return (falloc);
	// if (!(w->canvas.img.img_ptr = mlx_new_image(w->canvas.mlx_ptr,
	// 	W_WIDTH, W_HEIGHT)))
	// 	return (falloc);
	// if (!(w->canvas.img.img = (int*)mlx_get_data_addr(w->canvas.img.img_ptr,
	// 	&w->canvas.img.bpp, &w->canvas.img.stride, &w->canvas.img.endian)))
	// 	return (falloc);
	// mlx_hook(w->canvas.window, 2, 1, key_hook, w);
	// mlx_hook(w->canvas.window, 17, 0, hook_leave, w);
	// mlx_hook(w->canvas.window, 3, 1, key_unhook, w);
	// mlx_hook(fra->canvas.window, 4, 1, mouse_hook, fra);
	// mlx_hook(fra->canvas.window, 5, 1, mouse_unhook, fra);
	// mlx_hook(fra->canvas.window, 6, 6, mouse_notify, fra);
	// mlx_loop_hook(w->canvas.mlx_ptr, draw, w);
	// mlx_loop(w->canvas.mlx_ptr);
	return (ok);
}
