/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:27:26 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/06 20:26:14 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	parsing(t_data *data)
{
	t_lexer	*lexer;

	lexer = data->lexer_list;
	handle_exit_status(data);
	handle_heredoc(data, lexer);
	handle_command(data);
	delete_quotes_in_list(data->cmd_list);
}
