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

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WORD 1
# define PIPE 2
# define AMPERSAND 3
# define SEMICOLON 4
# define REDIRECTION 5
# define PARENTHESIS 6

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
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_data
{
	int		ac;
	char	**av;
	char	**env;
	char	**paths;
	char	*cmd;
	t_lexer	*lexer_list;
	t_env	*env_list;
}	t_data;

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);

char	*readline(const char *prompt);

int		is_space(char c);	
void	lexer(t_data *data);

int		init_data(t_data *data, int argc, char **env);
int		minishell(t_data *data);

#endif