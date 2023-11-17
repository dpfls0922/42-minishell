/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 22:53:36 by spark2            #+#    #+#             */
/*   Updated: 2023/04/04 18:43:06 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_sign(va_list *list, int *cnt, const char *format)
{
	if (*format == 'c')
		print_c(list, cnt);
	else if (*format == 's')
		print_s(list, cnt);
	else if (*format == 'p')
		print_p(list, cnt);
	else if (*format == 'd')
		print_d(va_arg(*list, int), cnt);
	else if (*format == 'i')
		print_d(va_arg(*list, int), cnt);
	else if (*format == 'u')
		print_u(va_arg(*list, unsigned int), cnt);
	else if (*format == 'x')
		print_x(va_arg(*list, unsigned int), cnt, 'x');
	else if (*format == 'X')
		print_x(va_arg(*list, unsigned int), cnt, 'X');
	else if (*format == '%')
		print_perc(cnt);
}

int	ft_printf(const char *format, ...)
{
	int		cnt;
	va_list	list;

	cnt = 0;
	va_start(list, format);
	while (*format)
	{
		if (cnt == -1)
			return (cnt);
		if (*format != '%')
		{
			if (ft_putchar(*format) == -1)
				cnt = -1;
			else
				cnt++;
		}
		else
		{
			format++;
			check_sign(&list, &cnt, format);
		}
		format++;
	}
	va_end(list);
	return (cnt);
}
