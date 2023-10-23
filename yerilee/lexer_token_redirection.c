/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:59:43 by marvin            #+#    #+#             */
/*   Updated: 2023/10/23 21:59:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	add_redirection(t_data *data, int i)
{
	int		start;
	int		len;
	char	*token;

	start = i;
	len = 0;
	while (data->cmd[i] && is_redirection(data->cmd[i]))
	{
		i++;
		len++;
	}
	token = ft_substr(data->cmd, start, len);
	data->lexer_list = add_token_to_lexer(data->lexer_list, token, REDIRECTION);
	free(token);
	token = NULL;
	return (i);
}
