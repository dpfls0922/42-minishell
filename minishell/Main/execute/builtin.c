/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:16:58 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/28 17:22:31 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(t_data *data, char **line)
{
	t_env	*curr;

	curr = data->env_list;
	if (line[1])
		no_such_file_error(line[1], 0);
	else
	{
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

void	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (cmd->cmd[i] && check_option_n(cmd->cmd[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd->cmd[i])
	{
		write(cmd->fd_out, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(cmd->fd_out, " ", 1);
		i++;
	}
	if (new_line)
		write(cmd->fd_out, "\n", 1);
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
		if (line[2])
			ft_error("exit: too many arguments\n");
		else
			exit(exit_code);
	}
}

int	is_builtin(t_cmd *cmd, t_data *data)
{
	char	*builtin;

	builtin = cmd->cmd[0];
	if (!data->cmd_list->cmd[0])
		return (2);
	if (!ft_strncmp_exec(builtin, "env", 4))
		builtin_env(data, cmd->cmd);
	else if (!ft_strncmp_exec(builtin, "pwd", 4))
		builtin_pwd(data);
	else if (!ft_strncmp_exec(builtin, "echo", 5))
		builtin_echo(cmd);
	else if (!ft_strncmp_exec(builtin, "cd", 3))
		builtin_cd(cmd->cmd[1]);
	else if (!ft_strncmp_exec(builtin, "export", 7))
		builtin_export(data, cmd->cmd);
	else if (!ft_strncmp_exec(builtin, "exit", 5))
		builtin_exit(cmd->cmd);
	else if (!ft_strncmp_exec(builtin, "unset", 6))
		builtin_unset(data, cmd->cmd);
	else
		return (0);
	return (1);
}
