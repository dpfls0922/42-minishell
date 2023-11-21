/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:13:20 by spark2            #+#    #+#             */
/*   Updated: 2023/11/21 21:36:41 by spark2           ###   ########.fr       */
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

void	cmd_not_found_error(char *cmd)
{
	printf("%s: command not found\n", cmd);
	unlink("/tmp/.infile");
	exit(127);
}
