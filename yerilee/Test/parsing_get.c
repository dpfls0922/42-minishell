/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:33:32 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/27 17:01:12 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	get_red_num(t_data *data)
{
	int		red_num;
	t_lexer	*curr;

	red_num = 0;
	curr = data->lexer_list;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == REDIRECTION && ft_strcmp(curr->val, "<<"))
			red_num++;
		curr = curr->next;
	}
	return (red_num);
}

char	*get_file_name(char *value)
{
	char	*file_name;

	file_name = ft_substr(value, 0, ft_strlen(value));
	return (file_name);
	// if (has_quotes(value))
	// 	file_name = delete_quotes(value);
	// else
	// 	file_name = ft_substr(value, 0, ft_strlen(value));
	// return (file_name);
}

int	get_fd_in(int *fd, int *red_type, int red_num)
{
	int	fd_in;
	int	i;

	fd_in = 0;
	i = 0;
	while (i < red_num)
	{
		if (red_type[i] == 1)
			fd_in = fd[i];
		i++;
	}
	return (fd_in);
}

int	get_fd_out(int *fd, int *red_type, int red_num)
{
	int	fd_out;
	int	i;

	fd_out = 1;
	i = 0;
	while (i < red_num)
	{
		if (red_type[i] == 2 || red_type[i] == 3)
			fd_out = fd[i];
		i++;
	}
	return (fd_out);
}
