/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:47:20 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/23 21:28:37 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_fork(t_cmd *cmd, t_data *data, int cnt)
{
	write(1, "in run fork\n", 12);
	if (pipe(cmd->pipe_fd) < 0)
		print_error("pipe error\n");
	// set_signal(DEFAUL T, DEFAULT);
	cmd->pid = fork();
	// printf("pid: %d\n", cmd->pid);
	// sleep(30);
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
		// printf("cmd: 1%s3\n", cmd->cmd[0]);
		if (cmd->cmd[0] == NULL) // "" (빈 문자열) 입력 시 에러 처리
			cmd_not_found_error("");
		if (!ft_strcmp(cmd->cmd[0], "/bin")
			|| !ft_strcmp(cmd->cmd[0], "/usr/bin"))
			is_a_dir_error(cmd->cmd[0]);
		if (data->pipe_flag)
		{
			if(cnt == 0)
				infile_to_pipe(cmd);
			else if (cnt == data->pipe_flag)
				pipe_to_outfile(cmd);
			else
				pipe_to_pipe(cmd);
		}
		// if (data->pipe_flag == 0) //if cmd.heredoc 존재하면 조건 추가하기
		// {
		// 	if (cmd->fd_in != 0)
		// 		dup2(cmd->fd_in, STDIN_FILENO);
		// 	if (cmd->fd_out != 1)
		// 		dup2(cmd->fd_out, STDOUT_FILENO);
		// }
		// else
		// {
		// 	if(cnt == 0)
		// 		infile_to_pipe(cmd);
		// 	else if (cnt == data->pipe_flag)
		// 		pipe_to_outfile(cmd);
		// 	else
		// 		pipe_to_pipe(cmd);
		// }
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
	while (curr) //cmd 갯수만큼 반복 (pipe + 1 개)
	{
		tmp_fd2 = dup(0);
		heredoc_flag = 0;
		if (curr->heredoc_num)
		{
			run_heredoc(data, data->end[cnt]);
			tmp_fd2 = dup(0);
			heredoc_flag = 1;
		}
		if (!(data->pipe_flag == 0 && is_builtin(data->cmd_list->cmd, data))) //!(pipe 없음 && builtin 함수임)
			cur_pid = run_fork(curr, data, cnt);
		curr = curr->next;
		cnt++;
		if (heredoc_flag)
			dup2(tmp_fd2, STDIN_FILENO);
	}
	//첫 번째 cmd가 cat이고 인자가 없음, pipe 있음
	// if (!ft_strcmp(data->cmd_list->cmd[0], "cat")
	// 	&& !data->cmd_list->cmd[1] && data->pipe_flag)
	// {
	// 	;
	// }
	// else
	// {
		waitpid(cur_pid, &status, 0);
		while (wait(0) != -1)
			;
	// }
	// if (!ft_strcmp(curr->cmd[0], "/bin")) // /bin의 exit_status 설정하기
	// 	{
	// 		g_vars.exit_status = 126;
	// 	}
	// else
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
