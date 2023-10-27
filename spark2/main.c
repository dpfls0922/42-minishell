/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:54:38 by spark2            #+#    #+#             */
/*   Updated: 2023/10/27 21:44:23 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	// t_arg	arg;
	char	**temp;

	(void)argv;
	if (!init_data1(&data, argc, envp))
		exit(1);
	// ft_memset(&arg, 0, sizeof(t_arg));
	if (argc > 3)
		set_file(&data, argc, argv);
	init_data_tmp(&data);

	// if (arg.here_flag)
	// run_heredoc(&arg, argv[2]);
	// get_path_envp(&arg, envp);
	// set_cmd(&arg, &cmd, argc, argv);
	// run_fork(&arg, &cmd, argc, envp);
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
		temp = ft_split(data.cmd, ' ');
		check_builtins(temp, &data);
		free(data.cmd);
		free(temp);
	}
	return (0);
}
