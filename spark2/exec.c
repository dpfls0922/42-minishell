/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:21:59 by spark2            #+#    #+#             */
/*   Updated: 2023/11/09 19:09:33 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_child(t_cmd *cmd, t_data *data, char **temp, int cnt)
{
	if (pipe(cmd->pipe_fd) < 0)
		print_error("pipe error\n");
	cmd->pid = fork();
	if (cmd->pid == -1)
		print_error("fork error\n");
	else if (cmd->pid == 0)
	{
		if (data->pipe_flag == 0) //if cmd.heredoc 존재하면 조건 추가하기
			;
		else if (cnt == 0)
			infile_to_pipe(data->cmd_list);
		else if (cnt == data->pipe_flag)
			pipe_to_outfile(data->cmd_list);
		else
			pipe_to_pipe(data->cmd_list);
		if (!is_builtin(temp, data))
			execve(get_cmd_path(cmd->path, cmd->cmd[0]),
				cmd->cmd, data->env);
	}
	else
		parent_work(data->cmd_list);
	return (cmd->pid);
}

void	exec_start(char **temp, t_data *data) //temp == data.cmd_list.cmd
{
	int		cur_pid;
	int		status;
	int		cnt;
	t_cmd	*curr;

	cnt = 0;
	curr = data->cmd_list;
	while (curr) //cmd 갯수만큼 반복 (pipe + 1 개)
	{
		if (data->pipe_flag == 0 && is_builtin(temp, data)) //pipe 없음 && builtin 함수임
			;
		else
		{
			// if (!is_builtin(temp, data)) //builtin 함수가 아니라면 자식 프로세스 실행
			cur_pid = exec_child(curr, data, temp, cnt);
		}
		curr = curr->next;
	}
	waitpid(cur_pid, &status, 0);
	while (wait(0) != -1)
		;
	data->exit_status = WEXITSTATUS(status);
}
