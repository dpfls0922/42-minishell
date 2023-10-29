/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:16:17 by spark2            #+#    #+#             */
/*   Updated: 2023/10/27 21:37:24 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setting_env(t_data *data)
{
	int	i;

	if (data->env)
	{
		i = 0;
		while (data->env[i])
		{
			data->env_list = add_env_to_list(data->env_list, data->env[i]);
			i++;
		}
	}
}

int	init_data1(t_data *data, int argc, char **envp)
{
	data->ac = argc;
	if (envp && envp[0])
		data->env = envp;
	setting_env(data);
	return (1);
}

void	init_data_tmp(t_data *data)
{
	data->cmd_list = malloc(sizeof(t_cmd));
	data->cmd_list->fd_out = 1;
	data->cmd_list->fd_in = 0;
	data->heredoc_num = 0;
}