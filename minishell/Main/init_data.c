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
			data->env_list = add_env_to_list(data, data->env[i], i);
			i++;
		}
	}
}

int	init_data1(t_data *data, int argc, char **env)
{
	data->ac = argc;
	data->prev_exit_status = 0;
	if (env && env[0])
		data->env = env;
	setting_env(data);
	return (1);
}

void	init_data2(t_data *data)
{
	data->heredoc_num = 0;
	data->pipe_flag = 0;
	data->lexer_list = NULL;
	data->cmd_list = NULL;
	g_exit_status = 0;
}

void	init_split(t_split *split, char *s, char c)
{
	split->len = 0;
	split->d_flag = 0;
	split->s_flag = 0;
	if (!s)
		return ;
	split->p = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!split->p)
		return ;
}

void	init_exit(t_data *data, t_exit *exit, char *value)
{
	exit->i = 0;
	exit->j = 0;
	exit->d_flag = 0;
	exit->s_flag = 0;
	exit->value = value;
	exit->prev_exit = ft_itoa(data->prev_exit_status, 0);
	exit->new_val = allocate_new_val(exit->prev_exit, value);
}
