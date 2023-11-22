/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:47:20 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/21 22:04:30 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_fork(t_cmd *cmd, t_data *data, char **temp, int cnt)
{
	if (pipe(cmd->pipe_fd) < 0)
		print_error("pipe error\n");
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
		if (!cmd->cmd[0]) // "" (빈 문자열) 입력 시 에러 처리
		{
			// printf("cmd.cmd: 1%s2\n", cmd->cmd[0]);
			cmd_not_found_error("");
		}
		if (!ft_strcmp(cmd->cmd[0], "/bin")) // /bin 입력 시 에러 처리
		{
			printf("/bin: is a directory\n");
			return (cmd->pid);
		}
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
		if (is_builtin(temp, data) == 0)
		{
			if (execve(get_cmd_path(cmd->path, cmd->cmd[0]),
					cmd->cmd, data->env) == -1)
			{
				printf("%s: No such file or directory\n", cmd->cmd[0]);
				g_vars.exit_status = 127;
				exit(127);
			}
		}
	}
	else
		parent_work(data->cmd_list);
	return (cmd->pid);
}

void	run_exec(char **temp, t_data *data) //temp == data.cmd_list.cmd
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
		printf("cmd.fd_in: %d\n", curr->fd_in);
		printf("cmd.fd_out: %d\n", curr->fd_out);
		tmp_fd = dup(0);
		tmp_fd2 = dup(0);
		heredoc_flag = 0;
		if (curr->heredoc_num)
		{
			run_heredoc(data, data->end[cnt]);
			tmp_fd2 = dup(0);
			heredoc_flag = 1;
		}
		printf("[heredoc_flag] : %d]\n", heredoc_flag);
		if (data->pipe_flag == 0 && is_builtin(temp, data)) //pipe 없음 && builtin 함수임
			;
		else
		{
			// if (!is_builtin(temp, data)) //builtin 함수가 아니라면 자식 프로세스 실행
			cur_pid = run_fork(curr, data, temp, cnt);
		}
		curr = curr->next;
		cnt++;
		if (heredoc_flag)
			dup2(tmp_fd2, STDIN_FILENO);
	}
	waitpid(cur_pid, &status, 0);
	while (wait(0) != -1)
		;
	// if (!ft_strcmp(curr->cmd[0], "/bin")) // /bin의 exit_status 설정하기
	// 	{
	// 		g_vars.exit_status = 126;
	// 	}
	// else
      g_vars.exit_status = WEXITSTATUS(status);
	dup2(tmp_fd, STDIN_FILENO);
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
		run_exec(data->cmd_list->cmd, data);
}
