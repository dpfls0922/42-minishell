/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:28:32 by spark2            #+#    #+#             */
/*   Updated: 2023/10/30 22:21:05 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_cmd *cmd, t_data *data)
{
	if (pipe(cmd->pipe_fd) < 0)
		print_error("pipe error\n");
	cmd->pid = fork();
	if (cmd->pid == -1)
		print_error("fork error\n");
	else if (cmd->pid == 0)
	{
		execve(get_cmd_path(cmd->path, cmd->cmd[0]),
			cmd->cmd, data->env);
	}
	// else
	// 	parent_work(arg);
	wait_process();
}

void	exec_start(char **temp, t_data *data)
{
	t_cmd	*curr;

	curr = data->cmd_list;
	while (curr->cmd)
	{
		// if (check_builtins(temp, data)) // && 파이프 없음
		// 	;
		// else
		// {
			exec_child(curr, data);
			check_builtins(temp, data);
		// }
		curr = curr->next;
	}
}