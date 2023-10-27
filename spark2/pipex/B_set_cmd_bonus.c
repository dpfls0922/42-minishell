/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_set_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:23:06 by spark2            #+#    #+#             */
/*   Updated: 2023/10/27 21:22:25 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	set_cmd(t_arg *arg, t_cmd *cmd, int argc, char **argv)
// {
// 	int	cmd_idx;
// 	int	argv_idx;
// 	int	size;

// 	cmd_idx = 0;
// 	argv_idx = -1;
// 	size = argc - 2;
// 	if (arg->here_flag)
// 	{
// 		argv_idx = 0;
// 		size = argc - 3;
// 	}
// 	cmd->arg = (t_cmd_arg *)malloc(sizeof(t_cmd_arg) * size);
// 	while (++argv_idx < argc - 3)
// 	{
// 		cmd->arg[cmd_idx].arr = ft_split(argv[argv_idx + 2], ' ');
// 		if (cmd->arg[cmd_idx].arr == NULL)
// 			print_error("cmd split error\n");
// 		cmd_idx++;
// 	}
// 	cmd->arg[cmd_idx].arr = 0;
// }
