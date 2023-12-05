/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:16:58 by yerilee           #+#    #+#             */
/*   Updated: 2023/12/05 18:09:01 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_cmd *cmd, t_data *data)
{
	int		fd;

	if (!data->cmd_list->cmd[0] && cmd->heredoc_num)
		return (2);
	if (data->pipe_flag != 0)
		fd = 1;
	else
		fd = cmd->fd_out;
	if (!ft_strncmp_exec(cmd->cmd[0], "env", 4))
		builtin_env(data, cmd, cmd->cmd);
	else if (!ft_strncmp_exec(cmd->cmd[0], "pwd", 4))
		builtin_pwd(data);
	else if (!ft_strncmp_exec(cmd->cmd[0], "echo", 5))
		builtin_echo(cmd, fd);
	else if (!ft_strncmp_exec(cmd->cmd[0], "cd", 3))
		builtin_cd(data, cmd, cmd->cmd[1]);
	else if (!ft_strncmp_exec(cmd->cmd[0], "export", 7))
		builtin_export(data, cmd, cmd->cmd);
	else if (!ft_strncmp_exec(cmd->cmd[0], "exit", 5))
		builtin_exit(cmd->cmd);
	else if (!ft_strncmp_exec(cmd->cmd[0], "unset", 6))
		builtin_unset(data, cmd->cmd);
	else
		return (0);
	return (1);
}
