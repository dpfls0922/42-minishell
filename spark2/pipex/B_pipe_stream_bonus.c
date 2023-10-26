/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_pipe_stream_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:35:22 by spark2            #+#    #+#             */
/*   Updated: 2023/10/26 21:27:25 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	infile_to_pipe(t_arg *arg)
{
	if (arg->infile < 0)
		print_error("infile error");
	close(arg->pipe_fd[0]);
	dup2(arg->infile, STDIN_FILENO);
	dup2(arg->pipe_fd[1], STDOUT_FILENO);
	close(arg->infile);
	close(arg->pipe_fd[1]);
}

void	pipe_to_pipe(t_arg *arg)
{
	dup2(arg->pipe_fd[1], STDOUT_FILENO);
	close(arg->pipe_fd[1]);
}

void	pipe_to_outfile(t_arg *arg)
{
	close(arg->pipe_fd[1]);
	dup2(arg->outfile, STDOUT_FILENO);
	close(arg->outfile);
}

void	parent_work(t_arg *arg)
{
	dup2(arg->pipe_fd[0], STDIN_FILENO);
	close(arg->pipe_fd[1]);
	close(arg->pipe_fd[0]);
}
