/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:01:10 by yerilee           #+#    #+#             */
/*   Updated: 2023/12/03 21:59:01 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	has_redirection_in_lexer(t_data *data)
{
	t_lexer	*curr;

	curr = data->lexer_list;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == REDIRECTION && ft_strcmp(curr->val, "<<"))
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	delete_node(t_data *data, int position)
{
	t_lexer	*curr;
	t_lexer	*temp;
	int		i;

	i = -1;
	curr = data->lexer_list;
	while (curr && ++i < position)
		curr = curr->next;
	if (curr)
	{
		if (curr && curr->next)
			curr->next->prev = curr->prev;
		if (curr && curr->prev)
			curr->prev->next = curr->next;
		temp = curr->next;
		free(curr->val);
		free(curr);
		curr = temp;
	}
	if (i == 0)
		data->lexer_list = curr;
}

void	delete_redirection_and_filename(t_data *data, int position, int flag)
{
	t_lexer	*curr;

	curr = data->lexer_list;
	while (curr && curr->type != PIPE)
	{
		flag = 0;
		if (curr && curr->type == REDIRECTION && ft_strcmp(curr->val, "<<"))
		{
			flag = 1;
			position++;
			curr = curr->next;
			if (curr && curr->type != REDIRECTION)
			{
				delete_node(data, position);
				position--;
				curr = curr->prev;
			}
			delete_node(data, position);
		}
		if (flag == 0)
			position++;
		if (curr)
			curr = curr->next;
	}
}

void	delete_redirection(t_data *data)
{
	while (has_redirection_in_lexer(data))
		delete_redirection_and_filename(data, 0, 0);
}
