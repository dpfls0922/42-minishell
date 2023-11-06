/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujin <sujin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:54:38 by spark2            #+#    #+#             */
/*   Updated: 2023/11/04 22:04:54 by sujin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (!init_data1(&data, argc, envp))
		exit(1);
	init_data_tmp(&data);
	check_signal();
	data.end[0] = argv[1]; //heredoc_test
	// set_cmd(&arg, &cmd, argc, argv);
	// run_free(&arg, &cmd, argc);
	// unlink("/tmp/.infile");
	while (1)
	{
		data.cmd = readline("minishell $ ");
		if (!data.cmd)
			break ;
		else if (!*data.cmd)
			free(data.cmd);
		if (data.cmd)
			add_history(data.cmd);
		data.cmd_list->cmd = ft_split(data.cmd, ' ');
		if (data.heredoc_num) //합칠 때 if (data.heredoc_num) 으로 수정
			run_heredoc(&data, data.end[0]); //합칠 때 limiter 매개변수 수정
		printf("fd_in: %d\n", data.cmd_list->fd_in);
		exec_start(data.cmd_list->cmd, &data);
		free(data.cmd);
		free(data.cmd_list->cmd);
	}
	return (0);
}
