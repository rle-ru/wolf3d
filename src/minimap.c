/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 23:25:43 by dacuvill          #+#    #+#             */
/*   Updated: 2019/07/13 16:00:33 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_square(t_wolf *w, int x, int y, int color)
{
	int		x2;
	int		yend;
	int		xend;
	int		i;

	yend = y + 9;
	xend = x + 9;
	i = y * W_WIDTH;
	while (y < yend)
	{
		x2 = x;
		while (x2 < xend)
		{
			w->canvas.img[i + x2] = color;
			++x2;
		}
		++y;
		i += W_WIDTH;
	}
}

static int		choose_color(t_wolf *w, int px, int py)
{
	if ((px == 0 || px == w->width - 1)
		|| (py == 0 || py == w->hei - 1))
		return (0x336600);
	else if (w->map[px][py] != 0)
		return (0x999966);
	else if ((int)(w->player.pos.x) == px
		&& (int)(w->player.pos.y) == py)
		return (0xcc0000);
	else
		return (0x3d3d29);
}

static void		init_focus_on_player(t_wolf *w)
{
	w->minimap.start_x = (int)w->player.pos.x - 10;
	w->minimap.end_x = (int)w->player.pos.x + 10;
	if (w->minimap.start_x < 0)
		w->minimap.end_x -= w->minimap.start_x;
	if (w->minimap.end_x >= w->width)
	{
		w->minimap.start_x -= w->minimap.end_x - w->width;
		w->minimap.end_x = w->width;
	}
	if (w->minimap.start_x < 0)
		w->minimap.start_x = 0;
	w->minimap.start_y = (int)w->player.pos.y - 10;
	w->minimap.end_y = (int)w->player.pos.y + 10;
	if (w->minimap.start_y < 0)
		w->minimap.end_y -= w->minimap.start_y;
	if (w->minimap.end_y >= w->hei)
	{
		w->minimap.start_y -= w->minimap.end_y - w->hei;
		w->minimap.end_y = w->hei;
	}
	if (w->minimap.start_y < 0)
		w->minimap.start_y = 0;
}

void			minimap(t_wolf *w)
{
	t_point	curr_px;
	int		px;
	int		py;

	init_focus_on_player(w);
	curr_px.y = 0;
	py = w->minimap.start_y;
	while (py < w->minimap.end_y)
	{
		curr_px.x = 0;
		px = w->minimap.start_x;
		while (px < w->minimap.end_x)
		{
			draw_square(w, curr_px.x, curr_px.y, choose_color(w, px, py));
			++px;
			curr_px.x += 10;
		}
		++py;
		curr_px.y += 10;
	}
}
