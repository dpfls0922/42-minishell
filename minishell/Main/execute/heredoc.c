/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:45:36 by sujin             #+#    #+#             */
/*   Updated: 2023/11/30 18:53:20 by spark2           ###   ########.fr       */
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

void	run_heredoc(t_cmd *cmd, char *limiter, int cnt)
{
	pid_t	pid;
	int		status;
	char	*gnl;
	char	*cnt_str;
	char	*here_doc_org;
	char	*here_doc_str;

	cnt_str = ft_itoa(cnt, 0);
	here_doc_org = "/tmp/.infile";
	here_doc_str = ft_strjoin_no_free(here_doc_org, cnt_str);
	cmd->fd_in = open(here_doc_str,
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
			write(cmd->fd_in, gnl, ft_strlen(gnl));
			ft_free_str(gnl);
			gnl = 0;
		}
		exit(0);
	}
	waitpid(pid, &status, 0);
	set_signal(SHELL, IGNORE);
	ft_free_str(gnl);
	close(cmd->fd_in);
	cmd->fd_in = open(here_doc_str, O_RDONLY, 0644);
}