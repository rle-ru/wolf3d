/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:06:09 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/22 09:08:30 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include <stdlib.h>

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
				return (badline);
			w->player.pos.x = x;
			w->player.pos.y = y;
			++lpos;
			w->parser.player = true;
			continue ;
		}
		w->map[y * w->width + x] = ft_atoi(line->line + lpos);
		while (line->line[lpos] && (ft_isdigit(line->line[lpos])
			|| line->line[lpos] == '-'))
			++lpos;
	}
	return (ok);
}

t_error			ft_create_map(t_wolf *w)
{
	int		y;
	t_line	*line;
	t_line	*tmp;
	t_error	ret;

	y = -1;
	w->width = w->parser.lines->nbx;
	if (!(w->map = malloc(w->width * w->height * sizeof(int))))
		return (falloc);
	line = w->parser.lines;
	while (++y < w->height && line != NULL)
	{
		if ((ret = ft_split_line(w, y, line)) != ok)
			return (ret);
		tmp = line;
		line = line->next;
		ft_memdel((void**)&tmp->line);
		ft_memdel((void**)&tmp);
	}
	w->parser.lines = NULL;
	w->parser.last_line = NULL;
	return (ok);
}
