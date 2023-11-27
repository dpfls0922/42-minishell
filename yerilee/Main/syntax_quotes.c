/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:34:42 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:34:42 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	check_closed_quote(int double_flag, int single_flag)
{
	if (double_flag || single_flag)
	{
		printf ("syntax error: unclosed quotation mark.\n");
		g_exit_status = 258;
		return (g_exit_status);
	}
	return (0);
}

int	check_quotes(t_lexer *lexer)
{
	t_lexer	*curr;
	int		i;
	int		double_flag;
	int		single_flag;

	curr = lexer;
	double_flag = 0;
	single_flag = 0;
	while (curr)
	{
		if (curr->type == WORD)
		{
			i = 0;
			while (curr->val[i])
			{
				if (curr->val[i] == '\"' && (single_flag == 0))
					double_flag = !double_flag;
				if (curr->val[i] == '\'' && (double_flag == 0))
					single_flag = !single_flag;
				i++;
			}
		}
		curr = curr->next;
	}
	return (check_closed_quote(double_flag, single_flag));
}
