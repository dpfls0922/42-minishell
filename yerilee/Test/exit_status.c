/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:10:04 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/29 20:51:11 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"


char	*change_exit_status(t_data *data, char *value)
{
	return (value);
}

void	handle_exit_status(t_data *data)
{
	int		i;
	int		double_flag;
	int		single_flag;
	t_lexer	*curr;

	double_flag = 0;
	single_flag = 0;
	curr = data->lexer_list;
	while (curr)
	{
		i = 0;
		while (curr->val[i])
		{
			if (curr->val[i] == '\"' && single_flag == 0)
				double_flag = !double_flag;
			if (curr->val[i] == '\'' && double_flag == 0)
				single_flag = !single_flag;
			if (single_flag == 0
				&& curr->val[i] == '$' && curr->val[i + 1] == '?')
				curr->val = change_exit_status(data, curr->val);
			i++;
		}
		curr = curr->next;
	}
}