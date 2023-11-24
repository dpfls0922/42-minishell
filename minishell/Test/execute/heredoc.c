/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:45:36 by sujin             #+#    #+#             */
/*   Updated: 2023/11/24 17:29:46 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_heredoc(t_data *data, t_cmd *cmd, char *limiter)
{
	char	*gnl;

	data->cmd_list->fd_in = open("/tmp/.infile", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	while (1)
	{
		write(1, "> ", 2);
		gnl = get_next_line(0);
		// printf("limiter : %s, gnl : %s\n", limiter, gnl);
		if (!limiter)
			break ;
		if (!ft_strncmp_gnl(limiter, gnl, ft_strlen(limiter)))
		{
			cmd->heredoc_num--;
			data->heredoc_num--;
			// printf("cmd.heredoc_nom : %d\n", data->cmd_list->heredoc_num);
			// printf("data.heredoc_nom : %d\n", data->heredoc_num);
			break ;
		}
		write(data->cmd_list->fd_in, gnl, ft_strlen(gnl));
		free(gnl);
		gnl = 0;
	}
	if (gnl)
	{
		free(gnl);
		gnl = 0;
	}
	close(data->cmd_list->fd_in);
	data->cmd_list->fd_in = open("/tmp/.infile", O_RDONLY, 0644);
}
