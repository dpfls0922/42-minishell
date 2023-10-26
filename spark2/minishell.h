/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:01:32 by spark2            #+#    #+#             */
/*   Updated: 2023/10/26 21:29:18 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "./libft/libft.h"
# include "./pipex/get_next_line/get_next_line.h"

typedef struct s_list_ms
{
	void			*content;
	struct s_list	*next;
}	t_list_ms;

typedef struct s_cmd_arg
{
	char	**arr;
}	t_cmd_arg;

typedef struct s_cmd
{
	t_cmd_arg	*arg;
}	t_cmd;

typedef struct s_arg
{
	int		infile;
	int		outfile;
	char	**path;
	int		pipe_fd[2];
	int		here_flag;
	pid_t	pid;
}	t_arg;

void	check_builtins(t_arg *arg, char **line, char **envp);
void	ft_error(char *str);
void	run_heredoc(t_arg *arg, char *limiter);

//pipex
void	check_argc(int argc);
void	set_file(t_arg *arg, int argc, char **argv);

void	run_heredoc(t_arg *arg, char *limiter);

void	get_path_envp(t_arg *arg, char **envp);
char	*get_cmd_path(char **path, char *cmd);

void	set_cmd(t_arg *arg, t_cmd *cmd, int argc, char **argv);

void	run_fork(t_arg *arg, t_cmd *cmd, int argc, char **envp);

void	run_free(t_arg *arg, t_cmd *cmd, int argc);
void	free_2d_array(char **str);
void	print_error(char *err_msg);

void	infile_to_pipe(t_arg *arg);
void	pipe_to_pipe(t_arg *arg);
void	pipe_to_outfile(t_arg *arg);
void	parent_work(t_arg *arg);

void	wait_process(void);

#endif