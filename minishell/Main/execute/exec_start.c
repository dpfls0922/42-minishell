/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:23:00 by spark2            #+#    #+#             */
/*   Updated: 2023/12/05 17:50:49 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	run_cmd(t_data *data, t_cmd *cmd)
{
	char	*path;

	if (is_builtin(cmd, data))
		exit(0);
	else
	{
		path = get_cmd_path(cmd->path, cmd->cmd[0]);
		if (execve(path, cmd->cmd, data->env) == -1)
			g_exit_status = 127;
	}
}

int	run_fork(t_cmd *cmd, t_data *data, int cnt)
{
	if (pipe(cmd->pipe_fd) < 0)
		print_error("pipe error\n");
	cmd->pid = fork();
	if (cmd->pid == -1)
		print_error("fork error\n");
	else if (cmd->pid == 0)
	{
		if (cmd->fd_in < 0 && data->pipe_flag == 0)
			exit(1);
		set_signal(DEFAULT, DEFAULT);
		child_work(cmd, data, cnt);
		run_cmd(data, cmd);
	}
	else
	{
		set_signal(IGNORE, IGNORE);
		parent_work(data->cmd_list);
	}
	return (cmd->pid);
}

int	run_exec(t_data *data)
{
	int		cnt;
	t_cmd	*curr;

	cnt = 0;
	curr = data->cmd_list;
	set_cmd_path(data);
	while (curr)
	{
		if (curr->fd_in != -2 && curr->fd_out != -2)
		{
			if (curr->cmd[0] == NULL && data->heredoc_num == 0)
				return (ft_free_list(curr->path));
			if (data->pipe_flag == 0 && is_builtin(data->cmd_list, data))
				return (ft_free_list(curr->path));
			else
				run_fork(curr, data, cnt);
		}
		ft_free_list(curr->path);
		curr = curr->next;
		cnt++;
	}
	g_exit_status = get_status();
	return (0);
}

void	executing(t_data *data)
{
	int		i;
	int		j;
	t_cmd	*curr;

	data->fd = dup_fd();
	i = 0;
	curr = data->cmd_list;
	while (i < data->heredoc_num)
	{
		j = -1;
		while (++j < curr->heredoc_num)
		{
			run_heredoc(curr, data->end[i], i);
			i++;
		}
		if (curr->next)
			curr = curr->next;
	}
	run_exec(data);
	redirect_fd(data->fd);
}
