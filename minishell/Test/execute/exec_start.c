/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:47:20 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/23 23:09:50 by yerilee          ###   ########.fr       */
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
	write(1, "in run fork\n", 12);
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
		if (!path)
			cmd_not_found_error(cmd->cmd[0]);
		if (cmd->cmd[0] == NULL) // "" (빈 문자열) 입력 시 에러 처리
			cmd_not_found_error("");
		if (!ft_strcmp(cmd->cmd[0], "/bin")
			|| !ft_strcmp(cmd->cmd[0], "/usr/bin"))
			is_a_dir_error(cmd->cmd[0]);
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

void	run_exec(t_data *data) //temp == data.cmd_list.cmd
{
	int		cur_pid;
	int		status;
	int		cnt;
	t_cmd	*curr;

	cnt = 0;
	curr = data->cmd_list;
	while (curr) //cmd 갯수만큼 반복 (pipe + 1 개)
	{
		if (curr->heredoc_num)
			run_heredoc(data, data->end[cnt]);
		if (!(data->pipe_flag == 0 && is_builtin(data->cmd_list->cmd, data))) //!(pipe 없음 && builtin 함수임)
			cur_pid = run_fork(curr, data, cnt);
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
	redirect_fd(data->fd);
}
