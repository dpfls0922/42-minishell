/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c_s_p_per.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:37:38 by spark2            #+#    #+#             */
/*   Updated: 2023/04/04 18:38:06 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_c(va_list *list, int *cnt)
{
	char	c;

	c = va_arg(*list, int);
	if (ft_putchar(c) == -1)
		*cnt = -1;
	else
		*cnt += 1;
}

void	print_s(va_list *list, int *cnt)
{
	char	*s;
	int		res;

	s = va_arg(*list, char *);
	res = ft_putstr(s);
	if (res == -1)
		*cnt = -1;
	else
		*cnt += res;
}

void	print_p(va_list *list, int *cnt)
{
	if (ft_putstr("0x") == -1)
	{
		*cnt = -1;
		return ;
	}
	print_p_scd(va_arg(*list, unsigned long long), cnt);
	*cnt += 2;
}

void	print_p_scd(unsigned long long n, int *cnt)
{
	if (n > 15)
	{
		print_p_scd(n / 16, cnt);
		n %= 16;
	}
	if (*cnt == -1)
		return ;
	if (ft_putchar("0123456789abcdef"[n]) == -1)
	{
		*cnt = -1;
		return ;
	}
	(*cnt)++;
}

void	print_perc(int *cnt)
{
	if (write(1, "%", 1) != 1)
		*cnt = -1;
	else
		(*cnt)++;
}
