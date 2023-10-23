/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:51:55 by marvin            #+#    #+#             */
/*   Updated: 2023/10/23 21:51:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	check_redirection_end(t_lexer *lexer)
{
	t_lexer	*curr;

	curr = lexer;
	while (curr->next)
		curr = curr->next;
	if (curr->type == REDIRECTION)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	check_redirection_len(t_lexer *lexer)
{
	t_lexer	*curr;

	curr = lexer;
	while (curr)
	{
		if (curr->type == REDIRECTION && ft_strlen(curr->val) > 2)
		{
			printf("syntax error near unexpected token `%s'\n", curr->val);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	check_command_after_redirection(t_lexer *lexer)
{
	t_lexer	*curr;

	curr = lexer;
	while (curr)
	{
		if (curr->type == REDIRECTION)
		{
			curr = curr->next;
			if (curr->next && (curr->type == PIPE || curr->type == REDIRECTION))
			{
				printf("syntax error near unexpected token `%s'\n", curr->val);
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

int	check_redirection(t_lexer *lexer)
{
	if (check_redirection_end(lexer) || check_redirection_len(lexer)
		|| check_command_after_redirection(lexer))
		return (1);
	return (0);
}
