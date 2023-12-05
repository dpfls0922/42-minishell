/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:00:53 by yerilee           #+#    #+#             */
/*   Updated: 2023/12/05 18:45:10 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	make_command_list(t_data *data, int red_num, int *red_type)
{
	int		*fd;
	char	*filename;
	int		i;
	t_lexer	*curr;

	filename = NULL;
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
			fd[i] = set_fd(filename, fd, red_type[i], i);
			i++;
			free(filename);
		}
		curr = curr->next;
	}
	delete_redirection(data);
	data->cmd_list = add_command_to_list(data, fd, red_type, red_num);
}

void	delete_command(t_data *data)
{
	t_lexer	*curr;

	curr = data->lexer_list;
	while (curr && curr->type != PIPE)
	{
		if (curr->next)
			curr->next->prev = curr->prev;
		if (curr->prev)
			curr->prev->next = curr->next;
		data->lexer_list = curr->next;
		free(curr->val);
		free(curr);
		curr = data->lexer_list;
	}
	if (curr && curr->type == PIPE)
	{
		if (curr->next)
			curr->next->prev = curr->prev;
		if (curr->prev)
			curr->prev->next = curr->next;
		data->lexer_list = curr->next;
		free(curr->val);
		free(curr);
		curr = data->lexer_list;
	}
}

void	handle_command(t_data *data)
{
	int	red_num;
	int	*red_type;

	set_pipe_flag(data, data->lexer_list);
	while (data->lexer_list)
	{
		red_num = get_red_num(data);
		red_type = set_red_type(data, red_num);
		make_command_list(data, red_num, red_type);
		delete_command(data);
	}
}
