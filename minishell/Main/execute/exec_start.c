/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:23:00 by spark2            #+#    #+#             */
/*   Updated: 2023/12/01 22:23:05 by yerilee          ###   ########.fr       */
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

int	get_status(void)
{
	int	i;
	int	status;

	i = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT && i++ == 0)
			{
				g_exit_status = 131;
				printf("^\\Quit: 3\n");
			}
			else if (WTERMSIG(status) == 2 && i++ == 0)
			{
				g_exit_status = 130;
				printf("^C\n");
			}
		}
	}
	return (g_exit_status);
}

int	run_fork(t_cmd *cmd, t_data *data, int cnt)
{
	char	*path;

	if (pipe(cmd->pipe_fd) < 0)
		print_error("pipe error\n");
	cmd->pid = fork();
	if (cmd->fd_in < 0 && data->pipe_flag == 0)
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	if (cmd->pid == -1)
		print_error("fork error\n");
	else if (cmd->pid == 0)
	{
		set_signal(DEFAULT, DEFAULT);
		child_work(cmd, data, cnt);
		if (is_builtin(cmd, data))
			exit(0);
		else
		{
			path = get_cmd_path(cmd->path, cmd->cmd[0]);
			if (execve(path, cmd->cmd, data->env) == -1)
				g_exit_status = 127;
		}
	}
	else
	{
		set_signal(IGNORE, IGNORE);
		parent_work(data->cmd_list);
	}
	return (cmd->pid);
}

void	run_exec(t_data *data)
{
	int		cur_pid;
	int		cnt;
	t_cmd	*curr;

	cnt = 0;
	curr = data->cmd_list;
	while (curr)
	{
		if (curr->fd_in != -2 && curr->fd_out != -2)
		{
			if (curr->cmd[0] == NULL && data->heredoc_num == 0)
				return ;
			if (data->pipe_flag == 0 && is_builtin(data->cmd_list, data))
				return ;
			else
				cur_pid = run_fork(curr, data, cnt);
		}
		curr = curr->next;
		cnt++;
	}
	g_exit_status = get_status();
}

void	executing(t_data *data)
{
	int		i;
	int		j;
	t_cmd	*curr;

	data->fd = dup_fd();
	curr = data->cmd_list;
	while (curr)
	{
		get_path_envp(curr, data->env);
		curr = curr->next;
	}
	i = -1;
	curr = data->cmd_list;
	while (++i < data->heredoc_num)
	{
		j = -1;
		while (++j < curr->heredoc_num)
			run_heredoc(curr, data->end[i], i);
		if (curr->next)
			curr = curr->next;
	}
	run_exec(data);
	redirect_fd(data->fd);
}
