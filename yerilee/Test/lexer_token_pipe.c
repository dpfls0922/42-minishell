/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:33:46 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:33:46 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_pipe(t_data *data, int i)
{
	int		start;
	int		len;
	char	*token;

	start = i;
	len = 0;
	while (data->cmd[i] && data->cmd[i] == '|')
	{
		i++;
		len++;
	}
	token = ft_substr(data->cmd, start, len);
	if (!token)
		exit (1);
	data->lexer_list = add_token_to_lexer(data->lexer_list, token, PIPE);
	free(token);
	token = NULL;
	return (i);
}
