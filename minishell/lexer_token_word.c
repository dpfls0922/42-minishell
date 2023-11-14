/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:34:17 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:34:17 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	is_space(char c)
{
	if (c == '\t' || c == '\n'
		|| c == '\r' || c == '\v'
		|| c == ' ' || c == '\f')
		return (1);
	return (0);
}

int	is_word(char c)
{
	if (c != '|' && c != '&' && c != ';'
		&& !is_space(c) && !is_redirection(c) && !is_parenthesis(c))
		return (1);
	return (0);
}

int	ft_word_len(char *cmd, int i)
{
	int		len;
	char	quote;

	len = 0;
	while (cmd[i] && is_word(cmd[i]))
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			quote = cmd[i];
			i++;
			len++;
			while (cmd[i] && cmd[i] != quote)
			{
				i++;
				len++;
			}
		}
		i++;
		len++;
	}
	return (len);
}

int	add_word(t_data *data, int i)
{
	char	*token;

	token = ft_substr(data->cmd, i, ft_word_len(data->cmd, i));
	if (!token)
		exit (1);
	i += ft_word_len(data->cmd, i);
	data->lexer_list = add_token_to_lexer(data->lexer_list, token, WORD);
	free(token);
	token = NULL;
	return (i);
}
