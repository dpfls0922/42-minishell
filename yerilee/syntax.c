/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:54:39 by marvin            #+#    #+#             */
/*   Updated: 2023/10/23 21:54:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	check_token_start(t_lexer *lexer)
{
	char	c;
	t_lexer	*curr;

	curr = lexer;
	if (curr->type == AMPERSAND || curr->type == PARENTHESIS
		|| curr->type == SEMICOLON)
	{
		c = curr->val[0];
		printf("Syntax error near unexpected token `%c'\n", c);
		return (1);
	}
	return (0);
}

int	check_syntax(t_lexer *lexer)
{
	if (!lexer)
		return (1);
	if (check_token_start(lexer) || check_quotes(lexer) || check_pipe(lexer)
		|| check_redirection(lexer))
		return (1);
	return (0);
}
