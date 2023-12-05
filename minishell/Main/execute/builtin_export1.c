/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:12:05 by yerilee           #+#    #+#             */
/*   Updated: 2023/12/05 18:49:41 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export2(t_cmd *cmd, char **env_strs)
{
	int	i;

	i = 0;
	while (env_strs[i])
	{
		write(cmd->fd_out, "declare -x ", 12);
		write(cmd->fd_out, env_strs[i], ft_strlen(env_strs[i]));
		write(cmd->fd_out, "\n", 1);
		i++;
	}
}

void	print_export1(t_data *data, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**splited_key1;
	char	**splited_key2;
	char	**env_strs;

	i = -1;
	env_strs = convert_env_list_to_export(data->env_list);
	while (env_strs[++i])
	{
		j = -1;
		while (env_strs[++j + 1])
		{
			splited_key1 = ft_split(env_strs[j], '=');
			splited_key2 = ft_split(env_strs[j + 1], '=');
			if (ft_strcmp(splited_key1[0], splited_key2[0]) > 0)
				ft_swap(&env_strs[j], &env_strs[j + 1]);
			ft_free_list(splited_key1);
			ft_free_list(splited_key2);
		}
	}
	print_export2(cmd, env_strs);
	ft_free_list(env_strs);
}

void	builtin_export(t_data *data, t_cmd *cmd, char **line)
{
	int		i;
	int		equal_idx;

	i = 0;
	if (!line[1])
	{
		if (cmd->fd_in != -1)
			print_export1(data, cmd);
	}
	else
	{
		while (line[++i])
		{
			equal_idx = check_env_exist(data->env_list, line[i]);
			if (!check_valid_arg("export", line[i]))
				;
			else if (equal_idx != -1)
				modify_env_value(data, line[i]);
			else
				add_env(data, line[i]);
		}
	}
}
