/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:27:17 by spark2            #+#    #+#             */
/*   Updated: 2023/10/11 21:03:03 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
}

// void	pwd(char **envp)
// {

// }

// void	unset(char **envp)
// {

// }

void	check_builtins(char *line, char **envp)
{
	if (!ft_strncmp(line, "env", 4))
		env(envp);
	// if (!ft_strncmp(line, "pwd", 4))
	// 	pwd(envp);
	// if (!ft_strncmp(line, "unset", 6))
	// 	unset(envp);
}
