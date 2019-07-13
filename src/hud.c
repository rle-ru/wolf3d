/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 10:32:18 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/13 10:49:04 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	character(t_wolf *w)
{
	int	tmp;
	int	y;
	int	ys;
	int	x;

	if (w->pc > 100)
		w->head ^= 1;
	if (w->pc > 100)
		w->pc = 0;
	w->pc++;
	y = W_GHEIGHT + 1;
	ys = y;
	while (y < W_HEIGHT)
	{
		x = CHAR_SX - 1;
		while (++x < CHAR_EX)
		{
			tmp = (((double)y - (double)ys) / 100.0) * w->text[8 + w->head]->h;
			w->canvas.img[y * W_WIDTH + x] =
				((int*)(w->text[8 + w->head]->pixels))[tmp * w->text[8
					+ w->head]->w + (int)((double)((x - CHAR_SX) / 100.0)
					* w->text[8 + w->head]->w)];
		}
		++y;
	}
}

void		draw_hud(t_wolf *w)
{
	int	x;
	int	y;
	int	i;

	y = W_GHEIGHT;
	i = y * W_WIDTH;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			w->canvas.img[i + x] = 0xFF;
			++x;
		}
		++y;
		i += W_WIDTH;
	}
	character(w);
}
