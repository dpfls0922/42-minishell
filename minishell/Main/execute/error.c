/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:13:20 by spark2            #+#    #+#             */
/*   Updated: 2023/11/15 16:26:41 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
}

void	print_error(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	unlink("/tmp/.infile");
	exit(1);
}
