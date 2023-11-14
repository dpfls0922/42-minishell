/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:54:02 by sujin             #+#    #+#             */
/*   Updated: 2023/11/14 16:45:01 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		show_prompt(void)
{

	rl_on_new_line(); //minishell $ 출력
	rl_replace_line("", 0); //버퍼 초기화
	rl_redisplay(); //없어도 일단 실행 됨
}

void	handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			ft_putstr_fd("\n", 1);
			show_prompt();
			g_vars.exit_status = 1;
		}
		else
			ft_putchar_fd('\n', 1);
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
			;
			// ft_putstr_fd("\b\b  \b\b", 1);
		else
			ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	set_signal(void)
{
	signal(SIGINT, handle_signal); //ctrl + C
	signal(SIGQUIT, handle_signal); //ctrl + /
}
