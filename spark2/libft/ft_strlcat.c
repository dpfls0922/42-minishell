/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:28:50 by spark2            #+#    #+#             */
/*   Updated: 2023/03/17 13:47:28 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	srcsize;
	size_t	dstsize;
	size_t	i;
	size_t	j;

	srcsize = ft_strlen(src);
	dstsize = ft_strlen(dest);
	i = dstsize;
	j = 0;
	if (size <= dstsize)
		return (srcsize + size);
	else
	{
		while (src[j] && dstsize + j + 1 < size)
		{
			dest[i] = src[j];
			i++;
			j++;
		}
		dest[i] = '\0';
	}
	return (srcsize + dstsize);
}
