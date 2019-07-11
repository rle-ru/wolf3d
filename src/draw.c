/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:02:05 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/11 17:26:15 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <math.h>
#include <SDL.h>

static void	update_hooks2(t_wolf *w, const uint8_t *s)
{
	double		tmp;

	if (s[SDL_SCANCODE_UP])
	{
		if ((tmp = w->player.pos.x + w->player.dir.x * w->ms + (w->player.dir.x < 0 ? -0.25 : 0.25)) >= 0 && (int)tmp < w->width)
			if (!w->map[(int)tmp][(int)w->player.pos.y])
				w->player.pos.x += w->player.dir.x * w->ms;
		if ((tmp = w->player.pos.y + w->player.dir.y * w->ms + (w->player.dir.y < 0 ? -0.25 : 0.25)) >= 0 && (int)tmp < w->height)
			if (!w->map[(int)w->player.pos.x][(int)tmp])
				w->player.pos.y += w->player.dir.y * w->ms;
	}
	else if (s[SDL_SCANCODE_DOWN])
	{
		if ((tmp = w->player.pos.x - w->player.dir.x * w->ms - (w->player.dir.x < 0 ? -0.25 : 0.25)) >= 0 && tmp < w->width)
			if (!w->map[(int)tmp][(int)w->player.pos.y])
				w->player.pos.x -= w->player.dir.x * w->ms;
		if ((tmp = w->player.pos.y - w->player.dir.y * w->ms - (w->player.dir.y < 0 ? -0.25 : 0.25)) >= 0 && tmp < w->height)
			if (!w->map[(int)w->player.pos.x][(int)tmp])
				w->player.pos.y -= w->player.dir.y * w->ms;
	}
	return ;
}

static void	update_hooks(t_wolf *w)
{
	const uint8_t	*s = SDL_GetKeyboardState(NULL);
	double			odx;
	double			opx;

	odx = w->player.dir.x;
	opx = w->player.plane.x;
	if (s[SDL_SCANCODE_ESCAPE])
		leave(ok, w);
	if (s[SDL_SCANCODE_LEFT])
	{
		w->player.dir.x = odx * cos(w->rs) - w->player.dir.y * sin(w->rs);
		w->player.dir.y = odx * sin(w->rs) + w->player.dir.y * cos(w->rs);
		w->player.plane.x = opx * cos(w->rs) - w->player.plane.y * sin(w->rs);
		w->player.plane.y = opx * sin(w->rs) + w->player.plane.y * cos(w->rs);
	}
	else if (s[SDL_SCANCODE_RIGHT])
	{
		w->player.dir.x = odx * cos(-w->rs) - w->player.dir.y * sin(-w->rs);
		w->player.dir.y = odx * sin(-w->rs) + w->player.dir.y * cos(-w->rs);
		w->player.plane.x = opx * cos(-w->rs) - w->player.plane.y * sin(-w->rs);
		w->player.plane.y = opx * sin(-w->rs) + w->player.plane.y * cos(-w->rs);
	}
	return (update_hooks2(w, s));
}

static void	update_fps(t_wolf *w)
{
	w->ot = w->t;
	w->t = SDL_GetTicks();
	w->ft = (w->t - w->ot) / 1000.0;
	w->fps = (1 / w->ft);
	w->ms = w->ft * 5.0;
	w->rs = w->ft * 3.0;
}

static void	IMPORTANT_THINGS(t_wolf *w)
{
	int	sx;
	int	ex;
	int	y;
	int	ys;
	int	x;

	if (w->pc > 100)
		w->head ^= 1;
	if (w ->pc > 100)
		w->pc = 0;
	w->pc++;
	sx = W_WIDTH / 2 - 50;
	ex = sx + 100;
	y = W_GHEIGHT + 1;
	ys = y;
	while (y < W_HEIGHT)
	{
		x = sx;
		while (x < ex)
		{
			int tmp = (((double)y - (double)ys) / 100.0) * w->text[8 + w->head]->h;
			w->canvas.img[y * W_WIDTH + x] 
				= ((int*)(w->text[8 + w->head]->pixels))[tmp * w->text[8 + w->head]->w + (int)((double)((x - sx) / 100.0) * w->text[8 + w->head]->w)];
				++x;
		}
		++y;
	}
}

int			draw(t_wolf *w)
{
	SDL_Event	event;

	while (1)
	{
		update_fps(w);
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			break ;
		ft_bzero(w->canvas.img, IMG_SIZE);
		update_hooks(w);
		ray_casting(w);
		IMPORTANT_THINGS(w);
		SDL_UpdateTexture(w->canvas.texture, NULL, w->canvas.img,
			W_WIDTH * 4);
		SDL_RenderCopy(w->canvas.renderer, w->canvas.texture, NULL, NULL);
		SDL_RenderPresent(w->canvas.renderer);
	}
	free(w->canvas.img);
	SDL_DestroyRenderer(w->canvas.renderer);
	SDL_Quit();
	return (0);
}
