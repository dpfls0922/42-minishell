/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:50:00 by spark2            #+#    #+#             */
/*   Updated: 2023/04/04 18:41:39 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);

size_t	ft_strlen(const char *str);
int		ft_putchar(char c);
int		ft_putstr(char *s);

void	print_c(va_list *list, int *cnt);
void	print_s(va_list *list, int *cnt);
void	print_p(va_list *list, int *cnt);
void	print_p_scd(unsigned long long n, int *cnt);
void	print_d(long long n, int *cnt);
void	print_u(unsigned int n, int *cnt);
void	print_x(unsigned int n, int *cnt, char flag);
void	print_perc(int *cnt);

#endif
