/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:27:26 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/26 21:41:22 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	make_command_list(t_data *data, int red_num, char *red_type)
{
	int		*fd;
	char	*filename;
	int		i;
	t_lexer	*curr;

	fd = malloc(sizeof(int) * red_num);
	if (!fd)
		exit (1);
	i = 0;
	curr = data->lexer_list;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == REDIRECTION && ft_strcmp(curr->val, "<<"))
		{
			curr = curr->next;
			filename = get_file_name(curr->val);
			fd[i] = set_fd(filename, red_type[i]);
			i++;
			free(filename);
		}
		curr = curr->next;
	}
	// redirection 지우기
	// delete_redirection(data);
	// cmd 구조체에 필요한 변수들 넘겨줘서, cmd_node를 만들어 cmd_list에 add하기
	// data->cmd_list = add_command_to_list(data, fd, red_num, red_type);
}

void	handle_command(t_data *data)
{
	int	red_num;
	int	*red_type;

	red_num = get_red_num(data);
	red_type = set_red_type(data, red_num);
	make_command_list(data, red_num, red_type);
}

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
