/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:54:02 by sujin             #+#    #+#             */
/*   Updated: 2023/11/27 19:43:09 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 1;
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		exit(1);
	}
}

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == HEREDOC)
		signal(SIGINT, handle_heredoc_signal);
	if (sig_int == IGNORE)
		signal(SIGINT, SIG_IGN);
	if (sig_int == DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (sig_int == SHELL)
		signal(SIGINT, handle_signal);
	if (sig_quit == IGNORE)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == SHELL)
		signal(SIGQUIT, handle_signal);
}
