/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 09:21:56 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/12 10:18:44 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <SDL.h>
#include <SDL_image.h>

static int		load_texture(t_wolf *w, char *path, int pos)
{
	SDL_Surface	*tmp;
	
	if (!(tmp = IMG_Load(path)))
		return (falloc);
	if (!(w->text[pos] = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888, 0)))
		return (falloc);
	SDL_FreeSurface(tmp);
	return (0);
}

static t_error	init_textures(t_wolf *w)
{
	int	error;

	error = 0;
	error |= load_texture(w, "pics/colorstone.png", 0);
	error |= load_texture(w, "pics/eagle.png", 1);
	error |= load_texture(w, "pics/greystone.png", 2);
	error |= load_texture(w, "pics/mossy.png", 3);
	error |= load_texture(w, "pics/redbrick.png", 4);
	error |= load_texture(w, "pics/purplestone.png", 5);
	error |= load_texture(w, "pics/wood.png", 6);
	error |= load_texture(w, "pics/jesuc.jpg", 7);
	error |= load_texture(w, "pics/rle-ru_right.png", 8);
	error |= load_texture(w, "pics/rle-ru_left.png", 9);
	return (error);
}

t_error	init_sdl(t_wolf *w)
{

	if (init_textures(w) != ok)
		return (falloc);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (falloc);
	if (!(w->canvas.window = SDL_CreateWindow(
					"Wolfenstein 3D",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					W_WIDTH,
					W_HEIGHT,
					SDL_WINDOW_SHOWN)))
		return (falloc);
	if (!(w->canvas.renderer = SDL_CreateRenderer(w->canvas.window, -1,
			SDL_RENDERER_ACCELERATED)))
		return (falloc);
	SDL_RenderSetLogicalSize(w->canvas.renderer, W_WIDTH, W_HEIGHT);
	if (!(w->canvas.texture = SDL_CreateTexture(w->canvas.renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		W_WIDTH, W_HEIGHT)))
		return (falloc);
	if (!(w->canvas.img = malloc(IMG_SIZE)))
		return (falloc);
	return (ok);
}
