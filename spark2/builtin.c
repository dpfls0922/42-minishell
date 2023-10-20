/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:27:17 by spark2            #+#    #+#             */
/*   Updated: 2023/10/20 20:25:11 by spark2           ###   ########.fr       */
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

void	pwd()
{
	char	*buf;

	buf = getcwd(0, 4096);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
}

int	check_option_n(char *token)
{
	int	i;

	if (ft_strncmp(token, "-n", 2))
		return (0);
	i = 2;
	while (token[i])
	{
		if (token[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(char **line)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (line[i] && check_option_n(line[i]))
	{
		new_line = 0;
		i++;
	}
	while (line[i])
	{
		write(1, line[i], ft_strlen(line[i]));
		if (line[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}

// void	unset(char **envp)
// {

// }

void	cd(char *path)
{
	if (!path)
		return ;
	chdir(path);
}

void	check_builtins(char **line, char **envp)
{
	char	*builtin;

	builtin = line[0];
	if (!ft_strncmp(builtin, "env", 4))
		env(envp);
	else if (!ft_strncmp(builtin, "pwd", 4))
		pwd();
	else if (!ft_strncmp(builtin, "echo", 5))
		echo(line);
	else if (!ft_strncmp(builtin, "cd", 3))
		cd(line[1]);
	// if (!ft_strncmp(line, "unset", 6))
		// unset(envp);
}
