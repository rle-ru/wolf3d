/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:06:09 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/12 09:34:15 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include <stdlib.h>

static t_error	check_player_spawn(t_wolf *w, int x, int y, int *lpos)
{
	if (w->parser.player == true)
		return (badline);
	w->player.pos.x = (double)x;
	w->player.pos.y = (double)y;
	++*lpos;
	w->parser.player = true;
	w->map[x][y] = 0;
	return (ok);
}

static t_error	ft_split_line(t_wolf *w, int y, t_line *line)
{
	int		x;
	int		lpos;
	int		tmp;

	x = -1;
	lpos = 0;
	while (++x < w->width)
	{
		while (line->line[lpos] && line->line[lpos] == ' ')
			++lpos;
		if (line->line[lpos] == 'P')
		{
			if (check_player_spawn(w, x, y, &lpos) == badline)
				return (badline);
			continue ;
		}
		tmp = ft_atoi(line->line + lpos);
		if (x == 0 || y == 0 || y == w->height - 1 || x == w->width - 1)
			tmp = !tmp ? 1 : tmp;
		tmp = tmp >= TEXTURES_N || tmp < 0 ? 1 : tmp;
		w->map[x][y] = tmp;
		while (line->line[lpos] && (ft_isdigit(line->line[lpos])
				|| line->line[lpos] == '-'))
			++lpos;
	}
	return (!(y == w->height - 1 && w->parser.player == false) ? ok : noplayer);
}

static void		init_wolf(t_wolf *w)
{
	w->player.dir.x = -1;
	w->player.dir.y = -0;
	w->player.plane.x = 0;
	w->player.plane.y = 0.66;
}

static t_error	fill_map(t_wolf *w)
{
	t_error	ret;
	t_line	*tmp;
	t_line	*line;
	int		y;

	y = -1;
	line = w->parser.lines;
	while (++y < w->height && line != NULL)
	{
		if ((ret = ft_split_line(w, y, line)) != ok)
			return (ret);
		tmp = line;
		line = line->next;
		ft_memdel((void**)&tmp->line);
		ft_memdel((void**)&tmp);
		w->parser.lines = line;
	}
	return (ret);
}

t_error			ft_create_map(t_wolf *w)
{
	t_error	ret;
	int		i;

	w->width = w->parser.lines->nbx;
	if (!(w->map = ft_memalloc(w->width * sizeof(int*))))
		return (falloc);
	i = 0;
	while (i < w->width)
	{
		if (!(w->map[i] = malloc(w->height * sizeof(int))))
			return (falloc);
		++i;
	}
	if ((ret = fill_map(w)) != ok)
		return (ret);
	init_wolf(w);
	w->parser.lines = NULL;
	w->parser.last_line = NULL;
	return (ret);
}
