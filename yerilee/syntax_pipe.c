/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:52:53 by marvin            #+#    #+#             */
/*   Updated: 2023/10/23 21:52:53 by marvin           ###   ########.fr       */
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
		return (1);
	}
	while (curr->next)
		curr = curr->next;
	if (curr->type == PIPE)
	{
		printf("syntax error: near unexpected token `|'.\n");
		return (1);
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
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	check_command_between_pipes(t_lexer *lexer)
{
	t_lexer	*curr;
	int		cmd_num;

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
				return (1);
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
		|| check_command_between_pipes(lexer))
		return (1);
	return (0);
}
