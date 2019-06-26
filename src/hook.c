/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:58:16 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/26 13:28:36 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "keys.h"

int			key_unhook(int key, t_wolf *w)
{
	w->keys[key] = false;
	return (0);
}

int			key_hook(int key, t_wolf *w)
{
	w->keys[key] = true;
	if (key == K_ESC)
		ft_leave(ok, w);
	return (0);
}
