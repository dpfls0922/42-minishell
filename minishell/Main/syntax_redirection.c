/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:34:47 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:34:47 by yerilee          ###   ########.fr       */
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
		g_exit_status = 258;
		return (g_exit_status);
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
			g_exit_status = 258;
			return (g_exit_status);
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
				g_exit_status = 258;
				return (g_exit_status);
			}
		}
		curr = curr->next;
	}
	return (0);
}

int	check_redirection(t_lexer *lexer)
{
	if (check_redirection_len(lexer) || check_redirection_end(lexer)
		|| check_command_after_redirection(lexer))
		return (g_exit_status);
	return (0);
}
