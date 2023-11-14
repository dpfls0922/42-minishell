/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:34:41 by spark2            #+#    #+#             */
/*   Updated: 2023/03/15 21:53:35 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*dstaddr;
	char	*srcaddr;
	size_t	i;

	dstaddr = (char *)dst;
	srcaddr = (char *)src;
	if (!dst && !src)
		return (dstaddr);
	if (dstaddr > srcaddr)
	{
		i = 0;
		while (i < n)
		{
			dstaddr[n - 1 - i] = srcaddr[n - 1 - i];
			i++;
		}
	}
	else
	{
		i = -1;
		while (++i < n)
			dstaddr[i] = srcaddr[i];
	}
	return (dstaddr);
}
