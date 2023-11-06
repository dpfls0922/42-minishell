/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujin <sujin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:54:02 by sujin             #+#    #+#             */
/*   Updated: 2023/11/04 22:05:10 by sujin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void interruptHandler()
{
	printf("this program will be exited in 3 seconds...\n");
	sleep(3);
	exit(0);
}

void    check_signal()
{
	signal(SIGINT, interruptHandler);
}

// int main()
// {
// 	signal(SIGINT, interruptHandler);
// 	printf("input ctrl+c\n");
// 	while (1);
// }