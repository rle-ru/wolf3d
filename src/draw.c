/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:02:05 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/11 09:49:21 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <math.h>
#include <SDL.h>

static void	update_hooks2(t_wolf *w, const uint8_t *s)
{
	double			tmp;
	double			dir2;

	if (s[SDL_SCANCODE_UP])
	{
		dir2 = w->player.dir.x;
		dir2 += (dir2 < 0 ? -20 : 20);
		if ((tmp = w->player.pos.x + dir2 * w->ms) >= 0 && (int)tmp < w->width)
			if (!w->map[(int)(tmp)][(int)w->player.pos.y])
				w->player.pos.x += w->player.dir.x * w->ms;
		dir2 = w->player.dir.y;
		dir2 += (dir2 < 0 ? -20 : 20);
		if ((tmp = w->player.pos.y + dir2 * w->ms) >= 0 && (int)tmp < w->height)
			if (!w->map[(int)w->player.pos.x][(int)(tmp)])
				w->player.pos.y += w->player.dir.y * w->ms;
	}
	else if (s[SDL_SCANCODE_DOWN])
	{
		dir2 = w->player.dir.x;
		dir2 += (dir2 < 0 ? -20 : 20);
		if ((tmp = w->player.pos.x - dir2 * w->ms) >= 0 && (int)tmp < w->width)
			if (!w->map[(int)(tmp)][(int)w->player.pos.y])
				w->player.pos.x -= w->player.dir.x * w->ms;
		dir2 = w->player.dir.y;
		dir2 += (dir2 < 0 ? -20 : 20);
		if ((tmp = w->player.pos.y - dir2 * w->ms) >= 0 && (int)tmp < w->height)
			if (!w->map[(int)w->player.pos.x][(int)(tmp)])
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
