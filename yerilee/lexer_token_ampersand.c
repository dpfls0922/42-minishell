/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_ampersand.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:03:29 by marvin            #+#    #+#             */
/*   Updated: 2023/10/23 22:03:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	add_ampersand(t_data *data, int i)
{
	int		start;
	int		len;
	char	*token;

	start = i;
	len = 0;
	while (data->cmd[i] && data->cmd[i] == '&')
	{
		i++;
		len++;
	}
	token = ft_substr(data->cmd, start, len);
	data->lexer_list = add_token_to_lexer(data->lexer_list, token, AMPERSAND);
	free(token);
	token = NULL;
	return (i);
}