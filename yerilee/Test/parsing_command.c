/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:06:48 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/28 21:07:14 by yerilee          ###   ########.fr       */
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
			fd[i] = set_fd(filename, red_type[i]);
			i++;
			free(filename);
		}
		curr = curr->next;
	}
	// printf("red_num : %d\n", red_num);
	// printf("red_type : %d\n", red_type[0]);
	// printf("fd : %d\n", fd[0]);
	// printf("filename : %s\n", filename);

	delete_redirection(data);
	// printf("====delete_redirection====\n");
	// print_lexer_list(data->lexer_list);
	data->cmd_list = add_command_to_list(data, fd, red_type, red_num);
	// printf("====add_command_to_list====\n");
	// print_command_list(data->cmd_list);
}

void	print_command_list(t_cmd *cmd_list)
{
	int		i;
	t_cmd	*curr;

	curr = cmd_list;
	while (curr)
	{
		i = 0;
		while (curr->cmd && curr->cmd[i])
		{
			printf("cmd : %s\n", curr->cmd[i]);
			i++;
		}	
		curr = curr->next;
	}
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

	red_num = get_red_num(data);
	red_type = set_red_type(data, red_num);
	while (data->lexer_list)
	{
		make_command_list(data, red_num, red_type);
		delete_command(data);
		printf("====delete_command====\n");
		print_lexer_list(data->lexer_list);
		printf("======================\n");
		print_command_list(data->cmd_list);
	}
}
