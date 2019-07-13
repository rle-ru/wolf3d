/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:06:33 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/13 10:36:54 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "wolf3d.h"

static t_error	ft_check_line(t_parser *parser, char *line)
{
	t_line		*new;

	if (!(new = malloc(sizeof(t_line))))
		return (falloc);
	if (parser->last_line == NULL)
		parser->lines = new;
	else
		parser->last_line->next = new;
	parser->last_line = new;
	new->line = line;
	new->next = NULL;
	if ((new->nbx = ft_countwords(line, ' ')) == 0
		|| new->nbx != parser->lines->nbx)
		return (badline);
	return (ok);
}

t_error			ft_parse_file(t_wolf *w)
{
	int		ret_gnl;
	char	*line;
	int		current_lines;
	t_error	ret;

	current_lines = 0;
	while ((ret_gnl = get_next_line(w->parser.fd, &line)) == 1)
	{
		++w->hei;
		if ((ret = ft_check_line(&w->parser, line)) != ok)
			return (ret);
	}
	if (ret_gnl == -1)
		return (falloc);
	if (w->parser.lines == NULL)
		return (badline);
	close(w->parser.fd);
	return (ok);
}
