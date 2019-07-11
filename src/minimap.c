/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 23:25:43 by dacuvill          #+#    #+#             */
/*   Updated: 2019/07/12 01:21:26 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		display_minimap(t_wolf *w, int px, int tmpy, int x, int y)
{
	int	tmpx;

	tmpx = px;
	while (tmpx < px + 9)
	{
		if ((x == 0 || x == w->width - 1) || (y == 0 || y == w->height - 1))
			w->canvas.img[tmpy * W_WIDTH + tmpx] = 0x336600;
		else if (w->map[x][y] != 0)
			w->canvas.img[tmpy * W_WIDTH + tmpx] = 0x999966;
		else if ((int)(w->player.pos.x) == x && (int)(w->player.pos.y) == y)
			w->canvas.img[tmpy * W_WIDTH + tmpx] = 0xcc0000;
		else
			w->canvas.img[tmpy * W_WIDTH + tmpx] = 0x3d3d29;
		tmpx++;
	}
}

void			minimap(t_wolf *w)
{
	int x;
	int y;
	int	px;
	int	py;
	int	tmpy;

	y = 0;
	py = 0;
	while (py < w->height * 10)
	{
		x = 0;
		px = 0;
		while (px < w->width * 10)
		{
			tmpy = py;
			while (tmpy < py + 9)
			{
				display_minimap(w, px, tmpy, x, y);
				tmpy++;
			}
			px += 10;
			++x;
		}
		py += 10;
		++y;
	}
}
