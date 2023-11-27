/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:34:36 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:34:36 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	check_pipe_start_end(t_lexer *lexer)
{
	t_lexer	*curr;

	curr = lexer;
	if (curr->type == PIPE)
	{
		printf("syntax error: near unexpected token `|'.\n");
		g_exit_status = 258;
		return (g_exit_status);
	}
	while (curr->next)
		curr = curr->next;
	if (curr->type == PIPE)
	{
		printf("syntax error: near unexpected token `|'.\n");
		g_exit_status = 258;
		return (g_exit_status);
	}
	return (0);
}

int	check_pipe_len(t_lexer *lexer)
{
	t_lexer	*curr;

	curr = lexer;
	while (curr)
	{
		if (curr->type == PIPE && ft_strlen(curr->val) > 1)
		{
			printf("syntax error near unexpected token `|'.\n");
			g_exit_status = 258;
			return (g_exit_status);
		}
		curr = curr->next;
	}
	return (0);
}

int	check_command_between_pipes(t_lexer *lexer, int cmd_num)
{
	t_lexer	*curr;

	curr = lexer;
	while (curr)
	{
		cmd_num = 0;
		if (curr->type == PIPE)
		{
			curr = curr->next;
			while (curr && curr->type != PIPE)
			{
				cmd_num++;
				curr = curr->next;
			}
			if (cmd_num == 0 && curr->type == PIPE)
			{
				printf("syntax error: near unexpected token `|'.\n");
				g_exit_status = 258;
				return (g_exit_status);
			}
		}
		if (curr && curr->type != PIPE)
			curr = curr->next;
	}
	return (0);
}

int	check_pipe(t_lexer *lexer)
{
	if (check_pipe_start_end(lexer) || check_pipe_len(lexer)
		|| check_command_between_pipes(lexer, 0))
		return (g_exit_status);
	return (0);
}
