/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:27:41 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/10 15:13:11 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>

static void		ft_inc(size_t size, size_t *n, void **src, void **dst)
{
	*n -= size;
	*src += size;
	*dst += size;
}

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*tmp;

	tmp = dst;
	while (n >= 8)
	{
		*(uint64_t*)(dst) = *(uint64_t*)(src);
		ft_inc(sizeof(uint64_t), &n, (void**)&src, &dst);
	}
	if (n >= 4)
	{
		*(uint32_t*)(dst) = *(uint32_t*)(src);
		ft_inc(sizeof(uint32_t), &n, (void**)&src, &dst);
	}
	if (n >= 2)
	{
		*(uint16_t*)(dst) = *(uint16_t*)(src);
		ft_inc(sizeof(uint16_t), &n, (void**)&src, &dst);
	}
	if (n >= 1)
		*(uint8_t*)dst = *(uint8_t*)src;
	return (tmp);
}
