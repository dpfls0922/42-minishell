/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_check_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:46:12 by spark2            #+#    #+#             */
/*   Updated: 2023/10/27 21:21:09 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_argc(int argc)
{
	if (argc < 5)
		perror("argc error\n"); //아래로 바꿔놓기
		// print_error("argc error\n");
}

void	set_file(t_data *data, int argc, char **argv)
{
	// if (!ft_strncmp(argv[1], "here_doc", 8)) //here_flag 받기
	// {
	// 	arg->here_flag = 1;
	// 	arg->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	// }
	// else
	// {
		data->cmd_list->fd_in = open(argv[1], O_RDONLY);
		data->cmd_list->fd_out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	// }
}
