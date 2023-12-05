/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:54:03 by yerilee           #+#    #+#             */
/*   Updated: 2023/12/05 16:54:29 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_free_data(t_data *data)
{
	if (data->heredoc_num)
		ft_free_list(data->end);
	if (data->lexer_list)
		ft_free_lexer(data->lexer_list);
	if (data->cmd_list)
		ft_free_cmd(data->cmd_list);
}

void	ft_free_path(t_cmd *cmd)
{
	t_cmd	*curr;
	t_cmd	*next;

	curr = cmd;
	while (curr)
	{
		next = curr->next;
		ft_free_list(curr->path);
		free(curr);
		curr = next;
	}
	curr = NULL;
	next = NULL;
}
