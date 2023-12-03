/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujin <sujin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:13:20 by spark2            #+#    #+#             */
/*   Updated: 2023/12/04 01:50:12 by sujin            ###   ########.fr       */
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
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 22);
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
	// ft_putstr_fd("export: `", 2);
	// ft_putstr_fd(str, 2);
	// ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_status = 1;
	return (0);
}
