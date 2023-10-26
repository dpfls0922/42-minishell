/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:27:26 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/26 21:50:41 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*

char	*set_command(t_data *data)
{
	char	*command;
	t_lexer	*curr;

	command = NULL;
	curr = data->lexer_list;
	while (curr && curr->type != PIPE)
	{
		command = ft_strjoin(command, curr->val);
		command = ft_strjoin(command, " ");
		curr = curr->next;
	}
	return (command);
}

t_cmd	*new_command_node(char *command, int fd_in, int fd_out)
{
	int		i;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		exit (1);
	// cmd->fd_in = fd_in;
	// cmd->fd_out = fd_out;
	return (cmd);
}

int	get_fd_in(int *fd, int red_num, int red_type)
{
	int	fd_in;
	int	i;

	fd_in = 0;
	i = 0;
	while (i < red_num)
	{
		if (red_type == 1)
			fd_in = fd[i];
		i++;
	}
	return (fd_in);
}

int	get_fd_out(int *fd, int red_num, int red_type)
{
	int	fd_out;
	int	i;

	fd_out = 1;
	i = 0;
	while (i < red_num)
	{
		if (red_type == 2 || red_type == 3)
			fd_out = fd[i];
		i++;
	}
	return (fd_out);
}

t_cmd	*add_command_to_list(t_data *data, int fd, int red_num, int *red_type)
{
	int		fd_in;
	int		fd_out;
	t_cmd	*node;
	t_cmd	*curr;
	char	*command;

	fd_in = get_fd_in(fd, red_num, red_type);
	fd_out = get_fd_out(fd, red_num, red_type);
	free(fd);
	free(red_type);
	command = set_command(data);
	node = new_command_node(command, fd_in, fd_out); // 구현 아직 x
	free(command);
	if (!node)
		exit(1);
	if (!data->cmd_list)
		return (node);
	curr = data->cmd_list;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = node;
	node->prev = curr;
	return (data->cmd_list);
}

*/

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

void	make_command_list(t_data *data, int red_num, int *red_type)
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

	// printf("red_num : %d\n", red_num);
	// printf("red_type : %d\n", red_type[0]);
	// printf("fd : %d\n", fd[0]);
	// printf("filename : %s\n", filename);

	// redirection 지우기
	// delete_redirection(data);
	// data->cmd_list = add_command_to_list(data, fd, red_num, red_type);
	// print_command_list(data->cmd_list);
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
