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

/* cmdline[0] = "echo", cmdline[1] = "hi", cmdline[2] = NULL */
typedef struct s_cmd {
	char	*cmdline;
	int		pipe_flag;
	char	quote;
}	t_cmd;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char	*readline(const char *prompt);

#endif