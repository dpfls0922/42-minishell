/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:56:12 by spark2            #+#    #+#             */
/*   Updated: 2023/12/05 17:07:11 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(SHELL, SHELL);
}

void	run_miniehll(t_data *data)
{
	expanding(data);
	parsing(data);
	executing(data);
	ft_free_data(data);
}

void	clear_and_free(t_data *data)
{
	rl_clear_history();
	ft_free_path(data->cmd_list);
	ft_free_env(data->env_list);
}

int	minishell(t_data *data)
{
	while (1)
	{
		set_signal(SHELL, SHELL);
		init_data2(data);
		data->cmd = readline("minishell $ ");
		if (!data->cmd)
			break ;
		else if (!*data->cmd)
			free(data->cmd);
		else if (data->cmd && data->cmd[0] != '\0')
		{
			lexer(data);
			if (check_syntax(data->lexer_list))
			{
				ft_free_lexer(data->lexer_list);
				data->prev_exit_status = g_exit_status;
				continue ;
			}
		}
		run_miniehll(data);
		data->prev_exit_status = g_exit_status;
	}
	clear_and_free(data);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data			data;
	struct termios	term;

	if (argc >= 2)
	{
		printf("%s : argv error\n", argv[1]);
		exit(127);
	}
	tcgetattr(STDIN_FILENO, &term);
	init_minishell();
	if (!init_data1(&data, argc, env))
		exit(1);
	if (!minishell(&data))
		return (0);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
