/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 08:11:48 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/10 11:27:05 by dacuvill         ###   ########.fr       */
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
	// ft_init_wolf(&w);// return values ?	
	return (0);
}
