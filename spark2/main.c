/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:54:38 by spark2            #+#    #+#             */
/*   Updated: 2023/10/11 21:02:01 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**temp;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		check_builtins(line, envp);
		temp = ft_split(line, ' ');
		free(line);
		//test
		int i = 0;
		while (temp[i])
		{
			printf("line %d: %s\n", i, temp[i]);
			i++;
		}
		free(temp);
	}
}
