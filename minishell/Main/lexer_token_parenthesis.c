/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_parenthesis.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:33:41 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:33:41 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	is_parenthesis(char c)
{
	if (c == '{' || c == '}'
		|| c == '(' || c == ')')
		return (1);
	return (0);
}

int	add_parenthesis(t_data *data, int i)
{
	int		start;
	int		len;
	char	*token;

	start = i;
	len = 0;
	while (data->cmd[i] && is_parenthesis(data->cmd[i]))
	{
		i++;
		len++;
	}
	token = ft_substr(data->cmd, start, len);
	if (!token)
		exit (1);
	data->lexer_list = add_token_to_lexer(data->lexer_list, token, PARENTHESIS);
	free(token);
	token = NULL;
	return (i);
}
