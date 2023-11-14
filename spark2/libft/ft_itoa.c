/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:35:24 by spark2            #+#    #+#             */
/*   Updated: 2023/03/18 20:52:15 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cnt_len(long long n)
{
	int		len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long long	nbr;
	int			i;
	int			len;
	char		*res;

	nbr = (long long)n;
	len = cnt_len(nbr);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len] = '\0';
	if (nbr < 0)
	{
		res[0] = '-';
		nbr *= -1;
	}
	if (!nbr)
		res[0] = '0';
	i = 1;
	while (nbr)
	{
		res[len - i++] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (res);
}
