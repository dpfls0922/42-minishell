/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:54:38 by spark2            #+#    #+#             */
/*   Updated: 2023/10/18 21:07:51 by spark2           ###   ########.fr       */
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
		temp = ft_split(line, ' ');
		check_builtins(temp, envp);
		free(line);
		free(temp);
	}
}
