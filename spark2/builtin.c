/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:27:17 by spark2            #+#    #+#             */
/*   Updated: 2023/10/26 22:11:54 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_arg arg, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(arg.outfile, envp[i], ft_strlen(envp[i]));
		write(arg.outfile, "\n", 1);
		i++;
	}
}

void	pwd(t_arg arg)
{
	char	*buf;

	buf = getcwd(0, 4096); //buf 사이즈 수정?
	write(arg.outfile, buf, ft_strlen(buf));
	write(arg.outfile, "\n", 1);
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

void	cd(char *path)
{
	if (!path)
		chdir(getenv("HOME"));
	else if (path[0] == '~')
	{
		if (!ft_strncmp(path, "~", 2))
			chdir(getenv("HOME"));
		else if (path[1] == '/')
		{
			chdir(getenv("HOME"));
			if (path[2])
				if (chdir(path) == -1)
					ft_error("No such file or directory\n");
		}
		else
			ft_error("No such file or directory\n");
	}
	else
		if (chdir(path) == -1)
			ft_error("No such file or directory\n");
}

void	unset(char **envp)
{
	(void)envp;
}

void	check_builtins(t_arg *arg, char **line, char **envp)
{
	char	*builtin;

	builtin = line[0];
	if (!ft_strncmp(builtin, "env", 4))
		env(*arg, envp);
	else if (!ft_strncmp(builtin, "pwd", 4))
		pwd(*arg);
	else if (!ft_strncmp(builtin, "echo", 5))
		echo(line);
	else if (!ft_strncmp(builtin, "cd", 3))
		cd(line[1]);
	if (!ft_strncmp(builtin, "unset", 6))
		unset(envp);
}
