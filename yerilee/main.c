/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:28:10 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/12 17:01:43 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *line)
{
	int	pipe_flag;

	pipe_flag = 0;
	while (*line)
	{
		line++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			add_history(line);
			// 사용자 입력 처리하기
			parse(line);
		}
		free(line);
	}
}
