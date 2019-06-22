/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 17:50:33 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/22 09:06:16 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wolf3d.h"
#include "libft.h"

void	free_lines(t_wolf *w)
{
	t_line	*cur;
	t_line	*tmp;

	cur = w->parser.lines;
	while (cur != NULL)
	{
		tmp = cur;
		if (cur->line)
			ft_memdel((void**)&cur->line);
		cur = cur->next;
		if (cur)
			ft_memdel((void**)&tmp);
	}
	w->parser.last_line = NULL;
	w->parser.lines = NULL;
}
