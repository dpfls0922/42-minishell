/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:34:05 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:34:05 by yerilee          ###   ########.fr       */
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
	if (!token)
		exit (1);
	data->lexer_list = add_token_to_lexer(data->lexer_list, token, REDIRECTION);
	free(token);
	token = NULL;
	return (i);
}
