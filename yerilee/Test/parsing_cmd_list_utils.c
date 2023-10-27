/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_list_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:42:27 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/27 21:33:03 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_cmd	*new_command_node(char *command, int fd_in, int fd_out)
{
	int		i;
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		exit (1);
	cmd->cmd = split_command(command, ' ');
	cmd->fd_in = fd_in;
	cmd->fd_out = fd_out;
	cmd->heredoc_num = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	i = 0;
	while (cmd->cmd && cmd->cmd[i])
	{
		if (ft_strcmp(cmd->cmd[i], "<<") == 0)
			cmd->heredoc_num++;
		i++;
	}
	printf("cmd->heredoc_num : %d\n", cmd->heredoc_num);
	return (cmd);
}

t_cmd	*add_command_to_list(t_data *data, int *fd, int *red_type, int red_num)
{
	int		fd_in;
	int		fd_out;
	t_cmd	*node;
	t_cmd	*curr;
	char	*command;

	fd_in = get_fd_in(fd, red_type, red_num);
	fd_out = get_fd_out(fd, red_type, red_num);
	free(fd);
	free(red_type);
	command = set_command(data);
	printf("fd_in : %d, fd_out : %d, command : %s\n", fd_in, fd_out, command);
	node = new_command_node(command, fd_in, fd_out);
	free(command);
	if (!data->cmd_list)
		return (node);
	curr = data->cmd_list;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = node;
	node->prev = curr;
	return (data->cmd_list);
}

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

void	handle_command(t_data *data)
{
	int	red_num;
	int	*red_type;

	red_num = get_red_num(data);
	red_type = set_red_type(data, red_num);
	make_command_list(data, red_num, red_type);
}
