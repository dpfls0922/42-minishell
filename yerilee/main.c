/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:28:10 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/12 16:46:14 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *s)
{

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
			// 사용자 입력 처리하기 - parsing
			parse(line);
		}
		free(line);
	}
}
