/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:01:32 by spark2            #+#    #+#             */
/*   Updated: 2023/11/10 21:32:13 by spark2           ###   ########.fr       */
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

typedef struct s_lexer
{
	char			*val;
	int				type;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_cmd
{
	char			**cmd; //
	int				fd_in; //
	int				fd_out; //
	int				heredoc_num; //
	char			**path; //
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
	int		ac; //
	char	**av;
	char	**env; //
	char	**paths;
	char	**end; //heredoc limiter
	char	*cmd;
	int		heredoc_num; //
	int		pipe_flag; //
	int		exit_status; //
	t_lexer	*lexer_list;
	t_env	*env_list; //
	t_cmd	*cmd_list; //
}	t_data;

//mine
int		is_builtin(char **line, t_data *data);
void	ft_error(char *str);
char	**ft_strjoin_2d(char **s1, char *s2);
void	init_data_tmp(t_data *data);
void	exec_start(char **temp, t_data *data);
void	run_heredoc(t_data *data, char *limiter);

//signal
void	interruptHandler(int sig);
void	check_signal(void);

//builtin
void	env(t_data *data);
void	pwd(t_data *data);
void	export(t_data *data, char **line);
void	builtin_unset(t_env *env, char **str);
void	builtin_export(t_data *data, char **line);
int		check_valid_arg(char *str);
int		check_env_exist(t_env *env, char *str);
void	builtin_env(t_data *data);
t_env	*new_env_node_no_value(char *str);

//utils
char	*ft_strndup(const char *src, int n);

//pipex
void	set_file(t_data *data, int argc, char **argv);

void	infile_to_pipe(t_cmd *cmd);
void	pipe_to_pipe(t_cmd *cmd);
void	pipe_to_outfile(t_cmd *cmd);
void	parent_work(t_cmd *cmd);

// void	run_heredoc(t_arg *arg, char *limiter);

void	get_path_envp(t_cmd *cmd, char **envp);
char	*get_cmd_path(char **path, char *cmd);

// void	set_cmd(t_arg *arg, t_cmd *cmd, int argc, char **argv);

// void	run_fork(t_arg *arg, t_cmd *cmd, int argc, char **envp);

// void	run_free(t_arg *arg, t_cmd *cmd, int argc);
// void	free_2d_array(char **str);
void	print_error(char *err_msg);

//yerin
t_env	*add_env_to_list(t_env *env, char *str);
t_env	*new_env_node(char *str);
int		init_data1(t_data *data, int argc, char **env);

#endif