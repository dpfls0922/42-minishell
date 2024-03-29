/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:27:17 by spark2            #+#    #+#             */
/*   Updated: 2023/11/17 19:41:03 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_data *data)
{
	t_env	*curr;

	curr = data->env_list;
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

	buf = getcwd(0, 4096); //buf 사이즈 수정?
	write(data->cmd_list->fd_out, buf, ft_strlen(buf));
	write(data->cmd_list->fd_out, "\n", 1);
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

void	builtin_cd(char *path) //홈 디렉토리가 env에서 제거되었을 경우 처리 필요
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
	if (!ft_strncmp(builtin, "env", 4))
		builtin_env(data);
	else if (!ft_strncmp(builtin, "pwd", 4))
		builtin_pwd(data);
	else if (!ft_strncmp(builtin, "echo", 5))
		builtin_echo(line);
	else if (!ft_strncmp(builtin, "cd", 3))
		builtin_cd(line[1]);
	else if (!ft_strncmp(builtin, "export", 7))
		builtin_export(data, line);
	else if (!ft_strncmp(builtin, "exit", 5))
		builtin_exit(line);
	else if (!ft_strncmp(builtin, "unset", 6))
		builtin_unset(data->env_list, line);
	else
		return (0);
	return (1);
}
