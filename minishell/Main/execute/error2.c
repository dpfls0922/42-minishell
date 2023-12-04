/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:03:54 by spark2            #+#    #+#             */
/*   Updated: 2023/12/04 18:04:34 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
