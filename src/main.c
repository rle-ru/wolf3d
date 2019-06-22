/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 08:11:48 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/22 15:30:09 by rle-ru           ###   ########.fr       */
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
		ft_leave(ret, &w);
	if ((ret = ft_parse_file(&w)) != ok)
		ft_leave(ret, &w);
	if ((ret = ft_create_map(&w)) != ok)
		ft_leave(ret, &w);
	// ft_init_wolf(&w);// return values ?
	if ((ret = init_mlx(&w)) != ok)
		ft_leave(ret, &w);
	return (0);
}
