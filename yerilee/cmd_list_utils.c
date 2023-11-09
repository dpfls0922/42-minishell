/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:00:48 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/09 14:04:37 by yerilee          ###   ########.fr       */
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
	command = set_command(data);
	free(fd);
	free(red_type);
	node = NULL;
	if (!command)
		return (node);
	node = new_command_node(command, fd_in, fd_out);
	delete_heredoc(node);
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

void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*curr;
	t_cmd	*next;

	curr = cmd;
	while (curr)
	{
		next = curr->next;
		if (curr->cmd)
			ft_free_list(curr->cmd);
		free(curr);
		curr = next;
	}
	curr = NULL;
	next = NULL;
}
