/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:54:38 by spark2            #+#    #+#             */
/*   Updated: 2023/11/10 23:05:05 by spark2           ###   ########.fr       */
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

	int	i;
	i = 1;
	t_cmd *tmp;
	tmp = data.cmd_list;
	tmp->cmd = ft_split(argv[1], ' ');
	tmp->next->cmd = ft_split(argv[2], ' ');
	exec_start(data.cmd_list->cmd, &data);

	//real code
	// while (1)
	// {
	// 	data.cmd = readline("minishell $ ");
	// 	if (!data.cmd)
	// 		break ;
	// 	else if (!*data.cmd)
	// 		free(data.cmd);
	// 	if (data.cmd)
	// 		add_history(data.cmd);
	// 	data.cmd_list->cmd = ft_split(data.cmd, ' ');
	// 	if (data.heredoc_num) //합칠 때 if (cmd.heredoc_num) 으로 수정
	// 		run_heredoc(&data, data.end[0]); //합칠 때 limiter 매개변수 수정
	// 	exec_start(data.cmd_list->cmd, &data);
	// 	free(data.cmd);
	// 	data.cmd = 0;
	// 	free(data.cmd_list->cmd);
	// 	data.cmd_list->cmd = 0;
	// }
	return (0);
}
