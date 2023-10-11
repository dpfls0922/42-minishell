/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:28:10 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/11 20:58:10 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_whitespace(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
			return (0);
		line++;
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break ;
		printf("flag : %d\n", is_only_whitespace(line));
		if (*line != '\0')
			add_history(line);
		if (*line != '\0' && !is_whitespace(line))
		{
			// 실행 부분
		}
		free(line);
	}
}
