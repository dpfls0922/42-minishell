/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:54:33 by spark2            #+#    #+#             */
/*   Updated: 2023/03/15 20:04:19 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *arr, int value, size_t len)
{
	size_t			i;
	unsigned char	*temp;

	temp = (unsigned char *)arr;
	i = 0;
	while (i < len)
		temp[i++] = value;
	return (temp);
}
