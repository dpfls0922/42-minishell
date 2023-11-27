/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:34:51 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:34:51 by yerilee          ###   ########.fr       */
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
		g_exit_status = 258;
		return (g_exit_status);
	}
	return (0);
}

int	check_syntax(t_lexer *lexer)
{
	if (!lexer)
		return (1);
	if (check_token_start(lexer) || check_quotes(lexer) || check_pipe(lexer)
		|| check_redirection(lexer))
		return (g_exit_status);
	return (0);
}
