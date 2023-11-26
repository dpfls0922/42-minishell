/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:52:16 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/27 01:33:54 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*ft_delete_quotes(char *s)
{
	int		i;
	int		len;
	int		quotes_len;
	int		*quotes_index;
	char	*new_str;

	quotes_index = get_quotes_index(s);
	quotes_len = get_quotes_len(s);
	new_str = malloc(ft_strlen(s) - quotes_len + 1);
	if (!new_str)
		exit (1);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (!is_quotes(i, quotes_index, quotes_len))
			new_str[len++] = s[i];
		i++;
	}
	new_str[len] = '\0';
	free(quotes_index);
	return (new_str);
}

char	*delete_quotes_in_str(char *str)
{
	char	*old;
	char	*new;

	old = NULL;
	new = NULL;
	if (has_quotes(str))
	{
		old = ft_substr(str, 0, ft_strlen(str));
		free(str);
		new = ft_delete_quotes(old);
		free(old);
	}
	else
		return (str);
	return (new);
}

void	delete_quotes_in_list(t_cmd *cmd_list)
{
	int		i;
	t_cmd	*curr;

	curr = cmd_list;
	while (curr && curr->cmd)
	{
		i = 0;
		while (curr->cmd[i])
		{
			curr->cmd[i] = delete_quotes_in_str(curr->cmd[i]);
			i++;
		}
		curr = curr->next;
	}
}
