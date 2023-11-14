/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:01:17 by spark2            #+#    #+#             */
/*   Updated: 2023/03/23 16:43:27 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dstaddr;
	char	*srcaddr;
	size_t	i;

	dstaddr = (char *)dst;
	srcaddr = (char *)src;
	i = -1;
	if (!dst && !src)
		return (dstaddr);
	while (++i < n)
		dstaddr[i] = srcaddr[i];
	return (dstaddr);
}
