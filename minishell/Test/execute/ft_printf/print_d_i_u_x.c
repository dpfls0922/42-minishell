/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d_i_u_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:00:55 by spark2            #+#    #+#             */
/*   Updated: 2023/04/04 18:41:05 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_d(long long n, int *cnt)
{
	if (n < 0)
	{
		n *= -1;
		if (ft_putchar('-') == -1)
		{
			*cnt = -1;
			return ;
		}
		else
			(*cnt)++;
	}
	if (n > 9)
	{
		print_d(n / 10, cnt);
		n %= 10;
	}
	if (*cnt == -1)
		return ;
	if (ft_putchar(n + '0') == -1)
	{
		*cnt = -1;
		return ;
	}
	(*cnt)++;
}

void	print_u(unsigned int n, int *cnt)
{
	if (n > 9)
	{
		print_u(n / 10, cnt);
		n %= 10;
	}
	if (*cnt == -1)
		return ;
	if (ft_putchar(n + '0') == -1)
	{
		*cnt = -1;
		return ;
	}
	(*cnt)++;
}

void	print_x(unsigned int n, int *cnt, char flag)
{
	char	*str;

	if (flag == 'x')
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	if (n > 15)
	{
		print_x(n / 16, cnt, flag);
		n %= 16;
	}
	if (*cnt == -1)
		return ;
	if (ft_putchar(str[n]) == -1)
	{
		*cnt = -1;
		return ;
	}
	(*cnt)++;
}
