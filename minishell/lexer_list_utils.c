/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:33:27 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:33:27 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_lexer	*new_lexer_node(char *token, int type)
{
	t_lexer	*node;
	int		i;

	node = malloc(sizeof(t_lexer));
	if (!node)
		exit(1);
	node->val = malloc(sizeof(char) * (ft_strlen(token) + 1));
	if (!node->val)
		exit(1);
	i = -1;
	while (token[++i])
		node->val[i] = token[i];
	node->val[i] = '\0';
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_lexer	*add_token_to_lexer(t_lexer *lexer, char *token, int type)
{
	t_lexer	*node;
	t_lexer	*curr;

	if (!token)
		return (NULL);
	node = new_lexer_node(token, type);
	if (!node)
		exit(1);
	if (!lexer)
		return (node);
	curr = lexer;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = node;
	node->prev = curr;
	return (lexer);
}
