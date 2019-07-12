/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 08:11:48 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/12 09:51:07 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

int		main(int ac, char **av)
{
	t_wolf	w;
	t_error	ret;

	ft_bzero(&w, sizeof(t_wolf));
	if ((ret = ft_open_file(ac, av, &w.parser)) != ok)
		leave(ret, &w);
	if ((ret = ft_parse_file(&w)) != ok)
		leave(ret, &w);
	if ((ret = ft_create_map(&w)) != ok)
		leave(ret, &w);
	if ((ret = init_sdl(&w)) != ok)
		leave(ret, &w);
	draw(&w);
	leave(ok, &w);
	return (0);
}
