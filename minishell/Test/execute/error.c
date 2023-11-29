/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:13:20 by spark2            #+#    #+#             */
/*   Updated: 2023/11/29 21:24:52 by yerilee          ###   ########.fr       */
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
	write(2, cmd, ft_strlen(cmd));
	write(2, " : command not found\n", 22);
	unlink("/tmp/.infile");
	exit(127);
}

void	no_such_file_error(char *cmd, int error_flag)
{
	printf("%s: No such file or directory\n", cmd);
	unlink("/tmp/.infile");
	if (error_flag)
		exit(127);
	g_exit_status = 127;
}

void	is_a_dir_error(char *cmd)
{
	printf("%s: is a directory\n", cmd);
	exit(126);
}
