/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:01:44 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/10 11:27:24 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <SDL.h>

static void		ft_usage(void)
{
	ft_fdprintf(STDERR_FILENO, "Usage :   ./wolf3d <map>\n");
}

static void		ft_print_error(t_error ret, t_wolf *w)
{
	if (ret == usage)
		ft_usage();
	else if (ret == filepath)
		ft_fdprintf(STDERR_FILENO, "Invalid file \"%s\"\n", w->parser.fname);
	else if (ret == falloc)
		ft_fdprintf(STDERR_FILENO, "A malloc failed\n");
	else if (ret == badline)
		ft_fdprintf(STDERR_FILENO, "Incorrect line : %d\n", w->height);
}

static void		ft_clear(t_wolf *w)
{
	if (w->parser.lines)
		free_lines(w);
	// if (w->map)
	// 	free(w->map);
}

int				leave(t_error ret, t_wolf *w)
{
	ft_print_error(ret, w);
	ft_clear(w);
	exit(0);
}

int				hook_leave(t_wolf *w)
{
	leave(ok, w);
	return (0);
}
