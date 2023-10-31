/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:01:32 by spark2            #+#    #+#             */
/*   Updated: 2023/10/31 22:16:39 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "./libft/libft.h"
# include "./pipex/get_next_line/get_next_line.h"

typedef struct s_list_ms
{
	void			*content;
	struct s_list	*next;
}	t_list_ms;

// typedef struct s_cmd_arg
// {
// 	char	**arr;
// }	t_cmd_arg;

// typedef struct s_cmd
// {
// 	t_cmd_arg	*arg;
// }	t_cmd;

// typedef struct s_arg
// {
// 	int		infile;
// 	int		outfile;
// 	char	**path;
// 	int		pipe_fd[2];
// 	int		here_flag;
// 	pid_t	pid;
// }	t_arg;

//yerin
typedef struct s_lexer
{
	char			*val;
	int				type;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_cmd
{
	char			**cmd;
	int				fd_in;
	int				fd_out;
	int				heredoc_num;
	char			**path;
	int				pipe_fd[2];
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_data
{
	int		ac;
	char	**av;
	char	**env;
	char	**paths;
	char	**end;
	char	*cmd;
	int		heredoc_num;
	int		pipe_flag;
	t_lexer	*lexer_list;
	t_env	*env_list;
	t_cmd	*cmd_list;
}	t_data;

//mine
int		check_builtins(char **line, t_data *data);
void	ft_error(char *str);
// void	run_heredoc(t_arg *arg, char *limiter);
char	**ft_strjoin_2d(char **s1, char *s2);
void	init_data_tmp(t_data *data);
void	exec_start(char **temp, t_data *data);

//builtin
void	env(t_data *data);
void	pwd(t_data *data);
void	export(t_data *data, char **line);
void	unset(t_env env);

//utils
char	*ft_strndup(const char *src, int n);

//yerin
t_env	*add_env_to_list(t_env *env, char *str);
int		init_data1(t_data *data, int argc, char **env);

//pipex
// void	check_argc(int argc);
void	set_file(t_data *data, int argc, char **argv);

// void	run_heredoc(t_arg *arg, char *limiter);

// void	get_path_envp(t_arg *arg, char **envp);
char	*get_cmd_path(char **path, char *cmd);

// void	set_cmd(t_arg *arg, t_cmd *cmd, int argc, char **argv);

// void	run_fork(t_arg *arg, t_cmd *cmd, int argc, char **envp);

// void	run_free(t_arg *arg, t_cmd *cmd, int argc);
// void	free_2d_array(char **str);
void	print_error(char *err_msg);

// void	infile_to_pipe(t_arg *arg);
// void	pipe_to_pipe(t_arg *arg);
// void	pipe_to_outfile(t_arg *arg);
// void	parent_work(t_arg *arg);

void	wait_process(void);

#endif