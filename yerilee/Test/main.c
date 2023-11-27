/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:34:27 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/27 19:46:35 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_data(t_data *data)
{
	if (data->heredoc_num)
		ft_free_list(data->end);
	if (data->lexer_list)
		ft_free_lexer(data->lexer_list);
	if (data->cmd_list)
		ft_free_cmd(data->cmd_list);
}

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
				data->prev_exit_status = g_exit_status;
				printf("[syntax] prev_exit_status : %d\n", data->prev_exit_status);
				continue ;
			}
			expanding(data);
			parsing(data);
			// execution
			ft_free_data(data);
		}
		data->prev_exit_status = g_exit_status;
	}
	rl_clear_history();
	ft_free_env(data->env_list);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc >= 2)
	{
		printf("%s : argv error\n", argv[1]);
		exit(127);
	}
	if (!init_data1(&data, argc, env))
		exit(1);
	if (!minishell(&data))
		return (0);
}
