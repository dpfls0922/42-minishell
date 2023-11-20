/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:27:17 by spark2            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/20 16:52:24 by spark2           ###   ########.fr       */
=======
/*   Updated: 2023/11/17 23:25:12 by yerilee          ###   ########.fr       */
>>>>>>> 1b0d5b55baf06b985b3414aede37a72c4e4ef99e
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(t_data *data)
{
	t_env	*curr;

	curr = data->env_list;
	if (!curr || !curr->val)
	{
		printf("env: No such file or directory\n");
		g_vars.exit_status = 127;
		return ;
	}
	while (curr)
	{
		if (!curr->val)
			break ;
		else
			printf("%s=%s\n", curr->key, curr->val);
		curr = curr->next;
	}
}

void	builtin_pwd(t_data *data)
{
	char	*buf;

	buf = getcwd(0, 4096);
	write(data->cmd_list->fd_out, buf, ft_strlen(buf));
	write(data->cmd_list->fd_out, "\n", 1);
	free(buf);
}

int	check_option_n(char *token)
{
	int	i;

	if (ft_strncmp_exec(token, "-n", 2))
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

void	builtin_echo(char **line)
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

void	builtin_cd(char *path)
{
	if (!path)
		chdir(getenv("HOME"));
	else if (path[0] == '~')
	{
		if (!ft_strncmp_exec(path, "~", 2))
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

void	builtin_exit(char **line)
{
	int	exit_code;

	printf("exit\n");
	if (!line[1])
		exit(0);
	else
	{
		exit_code = ft_atoi(line[1]);
		if (exit_code == -1)
		{
			printf("exit: %s: numeric argument required\n", line[1]);
			exit (255);
		}
		if (line[2])
			ft_error("exit: too many arguments\n");
		else
			exit(exit_code);
	}
}

int	is_builtin(char **line, t_data *data)
{
	char	*builtin;

	builtin = line[0];
	if (!data->cmd_list->cmd[0])
		return (2);
	if (!ft_strncmp_exec(builtin, "env", 4))
		builtin_env(data);
	else if (!ft_strncmp_exec(builtin, "pwd", 4))
		builtin_pwd(data);
	else if (!ft_strncmp_exec(builtin, "echo", 5))
		builtin_echo(line);
	else if (!ft_strncmp_exec(builtin, "cd", 3))
		builtin_cd(line[1]);
	else if (!ft_strncmp_exec(builtin, "export", 7))
		builtin_export(data, line);
	else if (!ft_strncmp_exec(builtin, "exit", 5))
		builtin_exit(line);
	else if (!ft_strncmp_exec(builtin, "unset", 6))
		builtin_unset(data->env_list, line);
	else
		return (0);
	return (1);
}
