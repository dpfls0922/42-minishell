/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:45:36 by sujin             #+#    #+#             */
/*   Updated: 2023/11/30 17:45:27 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_str(char *s)
{
	if (s)
	{
		free(s);
		s = 0;
	}
}

void	run_heredoc(t_data *data, char *limiter)
{
	pid_t	pid;
	int		status;
	char	*gnl;

	data->cmd_list->fd_in = open("/tmp/.infile",
			O_CREAT | O_WRONLY | O_TRUNC, 0666);
	set_signal(IGNORE, IGNORE);
	pid = fork();
	gnl = 0;
	if (pid == 0)
	{
		set_signal(HEREDOC, IGNORE);
		while (1)
		{
			write(1, "> ", 2);
			gnl = get_next_line(0);
			if (!gnl)
				break ;
			if (!limiter)
				break ;
			if (!ft_strncmp_gnl(limiter, gnl, ft_strlen(limiter)))
			{
				g_exit_status = 1;
				break ;
			}
			write(data->cmd_list->fd_in, gnl, ft_strlen(gnl));
			ft_free_str(gnl);
			gnl = 0;
		}
		exit(0);
	}
	waitpid(pid, &status, 0);
	set_signal(SHELL, IGNORE);
	ft_free_str(gnl);
	close(data->cmd_list->fd_in);
	data->cmd_list->fd_in = open("/tmp/.infile", O_RDONLY, 0644);
}
