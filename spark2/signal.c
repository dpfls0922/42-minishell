/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:54:02 by sujin             #+#    #+#             */
/*   Updated: 2023/11/06 21:36:44 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interruptHandler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		printf("exit\n");
	}
}

void	check_signal(void)
{
	signal(SIGINT, interruptHandler); //ctrl + C
	signal(SIGTERM, interruptHandler); //ctrl + D
	signal(SIGQUIT, interruptHandler); //ctrl + /
}
