/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:53:02 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/12 09:49:25 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "wolf3d.h"
#include "libft.h"

t_error	ft_open_file(int ac, char **av, t_parser *parser)
{
	if (ac != 2)
		return (usage);
	parser->fname = av[1];
	if (!ft_strcmp(av[1], "/dev/zero"))
		return (filepath);
	if ((parser->fd = open(av[1], O_RDONLY)) == -1)
		return (filepath);
	return (ok);
}
