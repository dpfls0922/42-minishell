/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:34:27 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/06 17:49:51 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(t_data *data)
{
	while (1)
	{
		init_data2(data);
		data->cmd = readline("minishell $ ");
		if (!data->cmd)
			break ;
		else if (!*data->cmd)
			free(data->cmd);
		else if (data->cmd && data->cmd[0] != '\0')
		{
			lexer(data);
			print_lexer_list(data->lexer_list);
			if (check_syntax(data->lexer_list))
			{
				ft_free_lexer(data->lexer_list);
				data->prev_exit_status = g_vars.exit_status;
				printf("[syntax] prev_exit_status : %d\n", data->prev_exit_status);
				continue ;
			}
			expanding(data);
			parsing(data);
			// execution
		}
		data->prev_exit_status = g_vars.exit_status;
		rl_clear_history();
		// free data
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	if (!init_data1(&data, argc, env))
		exit(1);
	if (!minishell(&data))
		return (0);
}
