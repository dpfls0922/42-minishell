/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:30:44 by spark2            #+#    #+#             */
/*   Updated: 2023/11/15 21:41:29 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	infile_to_pipe(t_cmd *cmd)
{
	if (cmd->fd_in < 0)
		print_error("fd_in error"); //에러 메세지 수정
	write(1, "infile to pipe\n", 15);
	close(cmd->pipe_fd[0]);
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	close(cmd->fd_in);
	close(cmd->pipe_fd[1]);
}

void	pipe_to_pipe(t_cmd *cmd)
{
	// close(cmd->pipe_fd[1]);
	// dup2(cmd->pipe_fd[0], STDIN_FILENO);
	close(cmd->pipe_fd[0]);
	dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	close(cmd->pipe_fd[1]);
	write(1, "pipe to pipe\n", 13);
}

void	pipe_to_outfile(t_cmd *cmd)
{
	write(1, "pipe to outfile\n", 16);
	// close(cmd->pipe_fd[1]);
	// dup2(cmd->pipe_fd[0], STDIN_FILENO);
	// close(cmd->pipe_fd[0]);
	close(cmd->pipe_fd[1]);
	dup2(cmd->fd_out, STDOUT_FILENO);
	// close(cmd->fd_out);
}

void	parent_work(t_cmd *cmd)
{
	// cmd->copied_fd_in = dup(cmd->fd_in);
	// cmd->copied_fd_out = dup(cmd->fd_out);
	dup2(cmd->pipe_fd[0], STDIN_FILENO);
	close(cmd->pipe_fd[1]);
	close(cmd->pipe_fd[0]);
}
