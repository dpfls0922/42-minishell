/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:10 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/24 21:59:49 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*dup_fd(void)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	return (fd);
}

void	redirect_fd(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	free(fd);
	fd = 0;
}

int	run_fork(t_cmd *cmd, t_data *data, int cnt)
{
	char	*path;

	if (pipe(cmd->pipe_fd) < 0)
		print_error("pipe error\n");
	cmd->pid = fork();
	if (cmd->fd_in < 0 && data->pipe_flag == 0)
	{
		g_vars.exit_status = 1;
		return (g_vars.exit_status);
	}
	if (cmd->pid == -1)
		print_error("fork error\n");
	else if (cmd->pid == 0)
	{
		if (cmd->cmd[0] == NULL)
			exit(0);
		path = get_cmd_path(cmd->path, cmd->cmd[0]);
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		if (data->pipe_flag)
		{
			if (cnt == 0)
				infile_to_pipe(cmd);
			else if (cnt == data->pipe_flag)
				pipe_to_outfile(cmd);
			else
				pipe_to_pipe(cmd);
		}
		if (is_builtin(cmd->cmd, data))
			exit(0);
		else
			execve(path, cmd->cmd, data->env);
	}
	else
		parent_work(data->cmd_list);
	return (cmd->pid);
}

void	run_exec(t_data *data)
{
	int		cur_pid;
	int		status;
	int		cnt;
	t_cmd	*curr;

	cnt = 0;
	curr = data->cmd_list;
	while (curr)
	{
		if (curr->fd_in != -2 && curr->fd_out != -2)
		{
			if (!(data->pipe_flag == 0 && is_builtin(data->cmd_list->cmd, data)))
				cur_pid = run_fork(curr, data, cnt);
		}
		curr = curr->next;
		cnt++;
	}
	waitpid(cur_pid, &status, 0);
	while (wait(0) != -1)
		;
	g_vars.exit_status = WEXITSTATUS(status);
}

void	executing(t_data *data)
{
	int		i;
	t_cmd	*curr;

	curr = data->cmd_list;
	data->fd = dup_fd();
	while (curr)
	{
		get_path_envp(curr, data->env);
		curr = curr->next;
	}
	i = -1;
	curr = data->cmd_list;
	while (data->heredoc_num)
	{
		while (curr->heredoc_num)
			run_heredoc(data, curr, data->end[++i]);
		if (curr->next)
			curr = curr->next;
	}
	run_exec(data);
	redirect_fd(data->fd);
}
