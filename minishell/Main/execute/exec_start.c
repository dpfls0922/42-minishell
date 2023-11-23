/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:10 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/23 21:29:35 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_fork(t_cmd *cmd, t_data *data, int cnt)
{
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
		char	*path;
		path = get_cmd_path(cmd->path, cmd->cmd[0]);
		if (!ft_strcmp(cmd->cmd[0], "/bin")
			|| !ft_strcmp(cmd->cmd[0], "/usr/bin"))
			is_a_dir_error(cmd->cmd[0]);
		if (data->pipe_flag == 0)
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
	int		tmp_fd1;
	int		tmp_fd2;
	int		cur_pid;
	int		status;
	int		cnt;
	int		heredoc_flag;
	t_cmd	*curr;

	cnt = 0;
	curr = data->cmd_list;
	tmp_fd1 = dup(0);
	while (curr)
	{
		tmp_fd2 = dup(0);
		heredoc_flag = 0;
		if (curr->heredoc_num)
		{
			run_heredoc(data, data->end[cnt]);
			tmp_fd2 = dup(0);
			heredoc_flag = 1;
		}
		if (!(data->pipe_flag == 0 && is_builtin(data->cmd_list->cmd, data)))
			cur_pid = run_fork(curr, data, cnt);
		curr = curr->next;
		cnt++;
		if (heredoc_flag)
			dup2(tmp_fd2, STDIN_FILENO);
	}
	waitpid(cur_pid, &status, 0);
	while (wait(0) != -1)
		;
	g_vars.exit_status = WEXITSTATUS(status);
	dup2(tmp_fd1, STDIN_FILENO);
}

void	executing(t_data *data)
{
	int		i;
	t_cmd	*curr;

	curr = data->cmd_list;
	while (curr)
	{
		get_path_envp(curr, data->env);
		curr = curr->next;
	}
	if (!data->cmd_list->cmd[0] && !data->pipe_flag)
	{
		i = -1;
		curr = data->cmd_list;
		while (curr->heredoc_num)
		{
			run_heredoc(data, data->end[++i]);
			if (curr->next)
				curr = curr->next;
		}
	}
	else
		run_exec(data);
}
