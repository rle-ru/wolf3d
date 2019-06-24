/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:12:11 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/24 15:08:47 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <stdint.h>
#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	int64_t		c2;
	char		*cpy;

	c2 = (int64_t)c << 56 | (int64_t)c << 48 | (int64_t)c << 40
		| (int64_t)c << 32 | c << 24 | c << 16 | c << 8 | c;
	cpy = (char*)b;
	while (len > 7)
	{
		*(int64_t*)(cpy) = (int64_t)c2;
		len -= 8;
		cpy += 8;
	}
	while (len > 0)
	{
		*cpy = c;
		++cpy;
	}
	return (b);
}
