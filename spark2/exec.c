/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:28:32 by spark2            #+#    #+#             */
/*   Updated: 2023/11/06 20:19:51 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_child(t_cmd *cmd, t_data *data)
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
	return (cmd->pid);
}

void	exec_start(char **temp, t_data *data) //temp == data.cmd_list.cmd
{
	int		cur_pid;
	int		status;
	t_cmd	*curr;

	curr = data->cmd_list;
	while (curr)
	{
		if (data->pipe_flag == 0 && is_builtin(temp, data)) //pipe 없음 && builtin 함수임
			;
		else
		{
			if (!is_builtin(temp, data)) //builtin 함수가 아니라면 자식 프로세스 실행
				cur_pid = exec_child(curr, data);
		}
		curr = curr->next;
	}
	waitpid(cur_pid, &status, 0);
	while (wait(0) != -1)
		;
	data->exit_status = WEXITSTATUS(status);
}
