/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:30:44 by spark2            #+#    #+#             */
/*   Updated: 2023/11/22 10:30:23 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	infile_to_pipe(t_cmd *cmd)
{
	if (cmd->fd_in < 0)
		return ;
	close(cmd->pipe_fd[0]);
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	close(cmd->pipe_fd[1]);
}

void	pipe_to_pipe(t_cmd *cmd)
{
	close(cmd->pipe_fd[0]);
	dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	close(cmd->pipe_fd[1]);
}

void	pipe_to_outfile(t_cmd *cmd)
{
	close(cmd->pipe_fd[1]);
	dup2(cmd->fd_out, STDOUT_FILENO);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
}

void	parent_work(t_cmd *cmd)
{
	dup2(cmd->pipe_fd[0], STDIN_FILENO);
	close(cmd->pipe_fd[1]);
	close(cmd->pipe_fd[0]);
}
