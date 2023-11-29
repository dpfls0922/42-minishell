/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:47:03 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/29 16:26:49 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(t_data *data, char **line)
{
	t_env	*curr;

	curr = data->env_list;
	if (line[1])
		no_such_file_error(line[1], 0);
	if (!curr || !curr->val)
	{
		printf("env: No such file or directory\n");
		g_exit_status = 127;
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

char	*get_minishell_env(char *env_val, t_env *env_list)
{
	t_env	*curr;
	char	*pwd;

	curr = env_list;
	pwd = NULL;
	while (curr)
	{
		if (!ft_strcmp(env_val, curr->val))
		{
			pwd = ft_substr(curr->val, 0, ft_strlen(curr->val));
			break ;
		}
		else
			curr = curr->next;
	}
	return (pwd);
}

void	builtin_pwd(t_data *data)
{
	char	*buf;

	buf = getcwd(0, 4096); //buf 사이즈 수정?
	// printf("buf: %s\n", buf);
	if (buf == NULL)
	{
		buf = get_minishell_env("PWD", data->env_list);
		if (!buf)
			buf = getenv("PWD");
		write(data->cmd_list->fd_out, buf, ft_strlen(buf));
		write(data->cmd_list->fd_out, "\n", 1);
	}
	else
	{
		write(data->cmd_list->fd_out, buf, ft_strlen(buf));
		write(data->cmd_list->fd_out, "\n", 1);
		free(buf);
	}
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

void	builtin_cd(char *path) //홈 디렉토리가 env에서 제거되었을 경우 처리 필요
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
		builtin_env(data, line);
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
