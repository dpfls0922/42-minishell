/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:14:47 by spark2            #+#    #+#             */
/*   Updated: 2023/03/23 19:33:33 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!(*s2))
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s2[j] && (i + j < len))
			{
				if (s1[i + j] != s2[j])
					break ;
				j++;
			}
		}
		if (!s2[j])
			return ((char *)&s1[i]);
		i++;
	}
	return (0);
}
