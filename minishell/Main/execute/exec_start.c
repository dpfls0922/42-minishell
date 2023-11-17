/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:38:06 by spark2            #+#    #+#             */
/*   Updated: 2023/11/17 19:52:23 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_fork(t_cmd *cmd, t_data *data, char **temp, int cnt)
{
	if (pipe(cmd->pipe_fd) < 0)
		print_error("pipe error\n");
	cmd->pid = fork();
	if (cmd->pid == -1)
		print_error("fork error\n");
	else if (cmd->pid == 0)
	{
		if (data->pipe_flag == 0) //if cmd.heredoc 존재하면 조건 추가하기
		{
			if (cmd->fd_in != 0)
				dup2(cmd->fd_in, STDIN_FILENO);
			if (cmd->fd_out != 1)
				dup2(cmd->fd_out, STDOUT_FILENO);
		}
		else if (cnt == 0)
			infile_to_pipe(cmd);
		else if (cnt == data->pipe_flag)
			pipe_to_outfile(cmd);
		else
			pipe_to_pipe(cmd);
		if (!is_builtin(temp, data))
		{
			if (execve(get_cmd_path(cmd->path, cmd->cmd[0]),
					cmd->cmd, data->env) == -1)
			{
				write(2, "command not found\n", 5);
				exit(42);
			}
		}
	}
	else
		parent_work(data->cmd_list);
	return (cmd->pid);
}

void	run_exec(char **temp, t_data *data)
{
	int		tmp_fd;
	int		cur_pid;
	int		status;
	int		cnt;
	t_cmd	*curr;

	cnt = 0;
	curr = data->cmd_list;
	tmp_fd = dup(0);
	while (curr)
	{
		if (data->pipe_flag == 0 && is_builtin(temp, data))
			;
		else
		{
			cur_pid = run_fork(curr, data, temp, cnt);
		}
		curr = curr->next;
		cnt++;
	}
	waitpid(cur_pid, &status, 0);
	while (wait(0) != -1)
		;
	data->prev_exit_status = WEXITSTATUS(status);
	dup2(tmp_fd, STDIN_FILENO);
}

void	executing(t_data *data)
{
	t_cmd	*curr;

	curr = data->cmd_list;
	while (curr)
	{
		get_path_envp(curr, data->env);
		curr = curr->next;
	}
	if (data->cmd_list->heredoc_num)
		run_heredoc(data, data->end[0]);
	run_exec(data->cmd_list->cmd, data);
}