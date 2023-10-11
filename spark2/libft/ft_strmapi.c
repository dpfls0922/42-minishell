/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:52:43 by spark2            #+#    #+#             */
/*   Updated: 2023/03/18 21:54:30 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*res;

	if (!s)
		return (0);
	len = ft_strlen(s);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	i = 0;
	while (s[i])
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}
