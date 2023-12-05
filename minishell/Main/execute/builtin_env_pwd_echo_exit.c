/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_pwd_echo_exit.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:07:08 by spark2            #+#    #+#             */
/*   Updated: 2023/12/05 18:09:58 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(t_data *data, t_cmd *cmd, char **line)
{
	t_env	*curr;

	curr = data->env_list;
	if (line[1])
		no_such_file_error("env", line[1], 127, 0);
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
			if (curr->val)
			{
				write(cmd->fd_out, curr->key, ft_strlen(curr->key));
				write(cmd->fd_out, "=", 1);
				write(cmd->fd_out, curr->val, ft_strlen(curr->val));
				write(cmd->fd_out, "\n", 1);
			}
			curr = curr->next;
		}
	}
}

void	builtin_pwd(t_data *data)
{
	char	*buf;

	(void)data;
	buf = getcwd(0, 4096);
	if (!buf)
	{
		printf("%s\n", buf);
		return ;
	}
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

void	builtin_echo(t_cmd *cmd, int fd)
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
		write(fd, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (new_line)
		write(fd, "\n", 1);
}

void	builtin_exit(char **line)
{
	int	exit_code;

	write(2, "exit\n", 5);
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
