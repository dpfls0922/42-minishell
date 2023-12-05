/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:43:57 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/12 16:43:57 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <dirent.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WORD 1
# define PIPE 2
# define AMPERSAND 3
# define SEMICOLON 4
# define REDIRECTION 5
# define PARENTHESIS 6

// Signals
# define SHELL 100
# define DEFAULT 101
# define IGNORE 102
# define HEREDOC 103

int	g_exit_status;

typedef struct s_lexer
{
	char			*val;
	int				type;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

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

typedef struct s_split
{
	char	**p;
	int		len;
	int		d_flag;
	int		s_flag;
}	t_split;

typedef struct s_exit
{
	int		i;
	int		j;
	int		d_flag;
	int		s_flag;
	char	*value;
	char	*prev_exit;
	char	*new_val;
}	t_exit;

typedef struct s_data
{
	int		ac;
	char	**av;
	char	**env;
	char	**end;
	char	*cmd;
	int		heredoc_num;
	int		pipe_flag;
	int		prev_exit_status;
	t_lexer	*lexer_list;
	t_env	*env_list;
	t_cmd	*cmd_list;
	int		*fd;
}	t_data;

char	*readline(const char *prompt);

/* Libft */
void	check_numeric(const char *str, int i);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	*ft_free(char **ptr, int i);
int		cnt_word(const char *s, char c);
char	*ft_word_dup(const char *src, char c);
char	**ft_split(char const *s, char c);
int		ft_strchr_idx(char *s, int c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp_exec(const char *s1, const char *s2);
char	*ft_strjoin_exec(char const *s1, char const *s2);
char	*ft_strjoin_no_free(char *s1, char *s2);
int		ft_strncmp_equal(const char *s1, const char *s2, size_t n);
int		ft_strncmp_exec(const char *s1, const char *s2, size_t n);
char	*ft_itoa(int nbr, int len);
int		count_len(int nbr);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *src);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);

/* lexer */
void	lexer(t_data *data);
void	ft_free_lexer(t_lexer *lexer);

t_lexer	*new_lexer_node(char *token, int type);
t_lexer	*add_token_to_lexer(t_lexer *lexer, char *token, int type);

int		is_space(char c);
int		is_word(char c);
int		is_redirection(char c);
int		is_parenthesis(char c);

int		ft_word_len(char *cmd, int i);
int		add_word(t_data *data, int i);
int		add_pipe(t_data *data, int i);
int		add_ampersand(t_data *data, int i);
int		add_semicolon(t_data *data, int i);
int		add_redirection(t_data *data, int i);
int		add_parenthesis(t_data *data, int i);

/* syntax */
int		check_syntax(t_lexer *lexer);
int		check_token_start(t_lexer *lexer);

int		check_pipe(t_lexer *lexer);
int		check_pipe_start_end(t_lexer *lexer);
int		check_pipe_len(t_lexer *lexer);
int		check_command_between_pipes(t_lexer *lexer, int cmd_num);

int		check_quotes(t_lexer *lexer);
int		check_closed_quote(int double_flag, int single_flag);

int		check_redirection(t_lexer *lexer);
int		check_redirection_end(t_lexer *lexer);
int		check_redirection_len(t_lexer *lexer);
int		check_command_after_redirection(t_lexer *lexer);

/* env */
t_env	*new_env_node(char *str);
t_env	*add_env_to_list(t_data *data, char *str, int i);
void	ft_free_env(t_env *env);

/* expanding */
int		has_variable(char *value);
void	expanding(t_data *data);
void	ft_expanding(t_data *data, t_lexer *lexer);

int		is_valid_env(t_data *data, char *var);
int		is_alnum(int c);
char	*find_env(char *str, int *i);
char	*get_value(t_data *data, char *key);

int		len_before_env(char *value, int *i);
int		len_after_env(char *value);
int		location_after_env(int i, char *value);

char	*str_after_env(char *value);
char	*strjoin_after_env(char *replaced_str, int i, char *lexer);
char	*str_without_env(char *lexer, char *replaced_val);

/* cmd_list */
t_cmd	*new_command_node(char *command, int fd_in, int fd_out);
t_cmd	*add_command_to_list(t_data *data, int *fd, int *red_type, int red_num);
void	ft_free_cmd(t_cmd *cmd);

/* parsing */
void	parsing(t_data *data);

void	handle_heredoc(t_data *data, t_lexer *lexer);
void	count_heredoc(t_data *data, t_lexer *lexer);
void	delete_heredoc(t_cmd *node);
char	**get_new_command(t_cmd *cmd);
char	**replace_with_new_command(char **new, char **cmd);

void	handle_command(t_data *data);
void	make_command_list(t_data *data, int red_num, int *red_type);

int		get_red_num(t_data *data);
char	*get_file_name(char *value);
int		get_fd_in(int *fd, int *red_type, int red_num);
int		get_fd_out(int *fd, int *red_type, int red_num);
void	fd_error(int fd, char *filename);
int		set_fd(char *filename, int *fd_arr, int red, int i);
int		*set_red_type(t_data *data, int red_num);
char	*set_command(t_data *data);
void	set_pipe_flag(t_data *data, t_lexer *lexer);

size_t	word_count(char *s, char c);
void	word_len(t_split *split, char c, int flag);
char	**ft_free_word(char	**p, int i);
int		ft_free_list(char **p);
char	**split_command(char *s, char c);

int		has_redirection_in_lexer(t_data *data);
void	delete_node(t_data *data, int position);
void	delete_redirection_and_filename(t_data *data, int position, int flag);
void	delete_redirection(t_data *data);

/* delete_quotes */
int		has_quotes(char *value);
char	*get_new_string(char *s, int position);
char	*ft_delete_quotes(char *s);
char	*delete_quotes_in_str(char *str);
void	delete_quotes_in_list(t_cmd *cmd_list);

/* delete_quotes_utils */
int		has_quotes(char *value);
int		is_quotes(int i, int *quotes_index, int quotes_len);
int		get_quotes_len(char *cmd);
int		*set_quotes_index(int *index, char *cmd);
int		*get_quotes_index(char *s);

/* exit_status */
void	handle_exit_status(t_data *data);
void	ft_change(t_data *data, t_lexer *curr);
char	*change_exit_status(t_data *data, char *value);
char	*allocate_new_val(char *prev_exit, char *value);

/* init_data */
void	setting_env(t_data *data);
int		init_data1(t_data *data, int argc, char **env);
void	init_data2(t_data *data);
void	init_split(t_split *split, char *s, char c);
void	init_exit(t_data *data, t_exit *exit, char *value);

/* free_utils */
void	ft_free_path(t_cmd *cmd);
void	ft_free_data(t_data *data);

/* builtin_cd1 */
char	**before_cd(t_data *data, char **old_pwd_export_2d);
void	after_cd(t_data *data, t_cmd *cmd, char **old_pwd, char **curr_pwd);
int		do_cd(t_data *data, char *path);
void	builtin_cd(t_data *data, t_cmd *cmd, char *path);

/* builtin_cd2 */
int		check_env_home_exist(t_env *env_list);
char	*get_minishell_env_key(char *env_key, t_env *env_list);
char	**make_pwd(char *str, char *arg_exist_flag);
int		cd_none_path(t_data *data);
int		cd_wave_path(char *path);

/* builtin_env_pwd_echo_exit */
void	builtin_env(t_data *data, t_cmd *cmd, char **line);
void	builtin_pwd(t_data *data);
int		check_option_n(char *token);
void	builtin_echo(t_cmd *cmd, int fd);
void	builtin_exit(char **line);

/* builtin */
int		is_builtin(t_cmd *cmd, t_data *data);

/* error1 */
void	ft_error(char *str);
void	print_error(char *err_msg);
void	cmd_not_found_error(char *cmd);

/* error2 */
void	no_such_file_error(char *cmd, char *str, int exit_code, int error_flag);
void	is_a_dir_error(char *cmd);
int		print_export_unset_error(char *cmd, char *str);

/* exec_set */
int		*dup_fd(void);
void	redirect_fd(int *fd);
void	set_cmd_path(t_data *data);

/* exec_start */
int		*dup_fd(void);
void	redirect_fd(int *fd);
void	executing(t_data *data);
int		run_fork(t_cmd *cmd, t_data *data, int cnt);
int		run_exec(t_data *data);
int		get_status(void);

/* export1 */
void	print_export2(t_cmd *cmd, char **env_strs);
void	print_export1(t_data *data, t_cmd *cmd);
void	builtin_export(t_data *data, t_cmd *cmd, char **line);

/* export2 */
char	**convert_env_list_to_export(t_env *node);
int		check_env_exist(t_env *env, char *str);
void	modify_env_value(t_data *data, char *str);
void	add_env(t_data *data, char *str);

/* heredoc */
void	ft_free_str(char *s);
void	run_heredoc(t_cmd *cmd, char *limiter, int cnt);

/* get_path_envp */
void	get_path_envp(t_cmd *cmd, char **envp);
char	*get_cmd_path(char **path, char *cmd);

/* pipe_stream */
void	infile_to_pipe(t_cmd *cmd);
void	pipe_to_pipe(t_cmd *cmd);
void	pipe_to_outfile(t_cmd *cmd);
void	parent_work(t_cmd *cmd);
void	child_work(t_cmd *cmd, t_data *data, int cnt);

/* signal */
void	show_prompt(void);
void	handle_signal(int signo);
void	set_signal(int sig_int, int sig_quit);

/* unset */
void	free_node(t_env *node);
void	remove_env(t_data *data, char *remove_str);
int		check_valid_arg(char *cmd, char *str);
void	builtin_unset(t_data *data, char **str);

/* utils */
char	**ft_strjoin_2d(char **s1, char *s2);
char	*ft_strndup(const char *src, int n);
void	ft_swap(char **a, char **b);
int		get_env_list_size(t_env *node);
t_env	*new_env_node_no_value(char *str);

/* main */
void	init_minishell(void);
void	run_miniehll(t_data *data);
void	clear_and_free(t_data *data);
int		minishell(t_data *data);

#endif