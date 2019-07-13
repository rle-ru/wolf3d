/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:01:44 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/13 10:36:54 by rle-ru           ###   ########.fr       */
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
		ft_fdprintf(STDERR_FILENO, "Incorrect line : %d\n", w->hei);
	else if (ret == noplayer)
		ft_fdprintf(STDERR_FILENO, "No player in map\n", w->hei);
}

static void		free_map(t_wolf *w)
{
	int	y;

	y = 0;
	while (y < w->hei)
	{
		ft_memdel((void**)&w->map[y]);
		++y;
	}
	ft_memdel((void**)(&w->map));
}

static void		ft_clear(t_wolf *w)
{
	int	i;

	i = 0;
	while (i < TEXTURES_N)
		SDL_FreeSurface(w->text[i++]);
	if (w->parser.lines)
		free_lines(w);
	if (w->map)
		free_map(w);
	ft_memdel((void**)w->canvas.img);
	SDL_DestroyWindow(w->canvas.window);
	SDL_DestroyRenderer(w->canvas.renderer);
	SDL_Quit();
}

int				leave(t_error ret, t_wolf *w)
{
	ft_print_error(ret, w);
	ft_clear(w);
	exit(0);
}
