/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:54:38 by spark2            #+#    #+#             */
/*   Updated: 2023/10/26 21:50:17 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;
	t_cmd	cmd;
	char	*line;
	char	**temp;

	(void)argc;
	(void)argv;
	ft_memset(&arg, 0, sizeof(t_arg));
	set_file(&arg, argc, argv);
	if (arg.here_flag)
		run_heredoc(&arg, argv[2]);
	get_path_envp(&arg, envp);
	set_cmd(&arg, &cmd, argc, argv);
	run_fork(&arg, &cmd, argc, envp);
	run_free(&arg, &cmd, argc);
	unlink("/tmp/.infile");

	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
	(void)envp;
	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break ;
		printf("here\n");
		if (*line)
			add_history(line);
		temp = ft_split(line, ' ');
		check_builtins(&arg, temp, envp);
		free(line);
		free(temp);
	}
}
