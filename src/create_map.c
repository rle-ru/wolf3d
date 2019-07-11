/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:06:09 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/11 14:56:53 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include <stdlib.h>

#include <stdio.h>

static t_error	ft_split_line(t_wolf *w, int y, t_line *line)
{
	int		x;
	int		lpos;

	x = -1;
	lpos = 0;
	while (++x < w->width)
	{
		while (line->line[lpos] && line->line[lpos] == ' ')
			++lpos;
		if (line->line[lpos] == 'P')
		{
			if (w->parser.player == true)
				return (badline); // same as below
			w->player.pos.x = (double)x;
			w->player.pos.y = (double)y;
			++lpos;
			w->parser.player = true;
			w->map[x][y] = 0;
			continue ;
		}
		w->map[x][y] = ft_atoi(line->line + lpos);
		while (line->line[lpos] && (ft_isdigit(line->line[lpos])
				|| line->line[lpos] == '-'))
			++lpos;
	}
	return ((w->parser.player == true) ? ok : ok);//better return value for no player
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
	t_line	*tmp;
	t_line	*line;

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
	return (ok);
}

t_error			ft_create_map(t_wolf *w)
{
	t_error	ret;
	int		y;
	int		i;

	y = -1;
	w->width = w->parser.lines->nbx;
	if (!(w->map = malloc(w->width * sizeof(int*))))
		return (falloc);
	i = 0;
	while (i < w->width)
	{
		if (!(w->map[i] = malloc(w->height * sizeof(int))))
			return (falloc);
		++i;
	}
	// if (!(w->map = malloc(w->width * w->height * sizeof(int))))
	// 	return (falloc);
	if (fill_map(w) != ok)
		return (badline);
	init_wolf(w);
	w->parser.lines = NULL;
	w->parser.last_line = NULL;
	return (ok);
}
