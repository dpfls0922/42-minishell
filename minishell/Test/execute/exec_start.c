/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:47:20 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/29 18:41:15 by spark2           ###   ########.fr       */
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
		g_exit_status = 1;
		return (g_exit_status);
	}
	if (cmd->pid == -1)
		print_error("fork error\n");
	else if (cmd->pid == 0)
	{
		if (cmd->cmd[0] == NULL)
			exit(0);
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
		if (curr->fd_in != -2 && curr->fd_out != -2)
		{
			if (data->pipe_flag == 0 && is_builtin(data->cmd_list, data))
				return ;
			else
				cur_pid = run_fork(curr, data, cnt);
		}
		curr = curr->next;
		cnt++;
	}
	if (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status)) //자식 프로세스가 정상 종료됨
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			// 자식 프로세스가 시그널을 받아 종료됨
			if (WTERMSIG(status) == SIGQUIT)
			{
				g_exit_status = 131;
				printf("QUIT: 3\n");
				printf("SIGQUIT received for PID %d\n", cur_pid);
			}
			else if (WTERMSIG(status) == 2) //자식 프로세스가 시그널 2(sigint)로 종료됨
			g_exit_status = 130;
		}
	}
	while (wait(0) != -1)
		;
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
