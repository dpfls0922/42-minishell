/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:33:23 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:33:23 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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

int	init_data1(t_data *data, int argc, char **env)
{
	data->ac = argc;
	if (env && env[0])
		data->env = env;
	setting_env(data);
	return (1);
}

void	init_data2(t_data *data)
{
	data->lexer_list = NULL;
}
