/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:00:28 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/27 20:28:34 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	*set_red_type(t_data *data, int red_num)
{
	int		i;
	int		*red_type;
	t_lexer	*curr;

	red_type = malloc(sizeof(int) * red_num);
	if (!red_type)
		exit (1);
	i = 0;
	curr = data->lexer_list;
	while (curr && curr->type != PIPE)
	{
		if (ft_strcmp(curr->val, "<") == 0)
			red_type[i++] = 1;
		if (ft_strcmp(curr->val, ">") == 0)
			red_type[i++] = 2;
		if (ft_strcmp(curr->val, ">>") == 0)
			red_type[i++] = 3;
		curr = curr->next;
	}
	return (red_type);
}

int	set_fd(char *filename, int red_type, int flag)
{
	int	fd;

	if (!ft_strcmp(filename, ""))
		fd = -2;
	else
	{
		if (red_type == 1)
			fd = open(filename, O_RDONLY | O_CLOEXEC);
		if (flag < 0)
			return (-1);
		if (red_type == 2)
			fd = open(filename, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0664);
		if (red_type == 3)
			fd = open(filename, O_RDWR | O_CREAT | O_APPEND | O_CLOEXEC, 0664);
	}
	if (fd == -1 || fd == -2)
	{
		printf("%s: No such file or directory\n", filename);
		g_exit_status = 1;
	}
	return (fd);
}

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

void	set_pipe_flag(t_data *data, t_lexer *lexer)
{
	while (lexer)
	{
		if (!ft_strcmp(lexer->val, "|"))
			data->pipe_flag++;
		lexer = lexer->next;
	}
}
