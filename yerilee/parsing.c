/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:27:26 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/27 17:01:43 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/* $? 처리 -> heredoc 처리 -> command_list 만들기 -> quotes 제거 */
void	parsing(t_data *data)
{
	t_lexer	*lexer;

	lexer = data->lexer_list;
	// $? 처리
	handle_heredoc(data, lexer);
	handle_command(data);
	// quotes 제거
}
