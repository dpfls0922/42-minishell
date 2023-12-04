/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:49:12 by spark2            #+#    #+#             */
/*   Updated: 2023/12/04 16:19:22 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	g_exit_status = 1;
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

void	no_such_file_error(char *cmd, char *str, int exit_code, int error_flag)
{
	if (cmd)
		printf("%s: ", cmd);
	printf("%s: No such file or directory\n", str);
	unlink("/tmp/.infile");
	if (error_flag)
		exit(exit_code);
	g_exit_status = exit_code;
}

void	is_a_dir_error(char *cmd)
{
	printf("%s: is a directory\n", cmd);
	exit(126);
}

int	print_export_unset_error(char *cmd, char *str)
{
	printf("%s: ", cmd);
	printf("`%s': not a valid identifier\n", str);
	g_exit_status = 1;
	return (0);
}
