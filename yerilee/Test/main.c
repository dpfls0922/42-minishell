/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:34:27 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/25 21:49:40 by yerilee          ###   ########.fr       */
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
				continue ;
			}
			expanding(data);
			// parser
			// execution
		}
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
