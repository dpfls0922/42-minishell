/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_run_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:33:01 by spark2            #+#    #+#             */
/*   Updated: 2023/10/30 22:20:10 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	run_fork(t_arg *arg, t_cmd *cmd, int argc, char **envp)
// {
// 	int		i;

// 	i = -1;
// 	while (++i < argc - 3 - arg->here_flag)
// 	{
// 		if (pipe(arg->pipe_fd) < 0)
// 			print_error("pipe error\n");
// 		arg->pid = fork();
// 		if (arg->pid == -1)
// 			print_error("fork error\n");
// 		else if (arg->pid == 0)
// 		{
// 			if (i == 0)
// 				infile_to_pipe(arg);
// 			else if (i == argc - 4 - arg->here_flag)
// 				pipe_to_outfile(arg);
// 			else
// 				pipe_to_pipe(arg);
// 			execve(get_cmd_path(arg->path, cmd->arg[i].arr[0]),
// 				cmd->arg[i].arr, envp);
// 		}
// 		else
// 			parent_work(arg);
// 	}
// 	wait_process();
// }

void	wait_process(void)
{
	while (wait(0) != -1)
		;
}
