/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:01:32 by spark2            #+#    #+#             */
/*   Updated: 2023/10/11 21:02:18 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "./libft/libft.h"

void	check_builtins(char *line, char **envp);

#endif