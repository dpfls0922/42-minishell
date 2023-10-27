/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_free_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:15:30 by spark2            #+#    #+#             */
/*   Updated: 2023/10/27 21:21:31 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_2d_array(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

// void	run_free(t_arg *arg, t_cmd *cmd, int argc)
// {
// 	int	i;

// 	free_2d_array(arg->path);
// 	i = -1;
// 	while (++i < argc - 3 - arg->here_flag)
// 		free_2d_array(cmd->arg[i].arr);
// 	free(cmd->arg);
// }

void	print_error(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	unlink("/tmp/.infile");
	exit(1);
}
