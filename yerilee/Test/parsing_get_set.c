/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:49:57 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/26 21:18:03 by yerilee          ###   ########.fr       */
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
}

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

int	set_fd(char *filename, int red_type)
{
	int	fd;

	if (red_type == 1)
		fd = open(filename, O_RDONLY | O_CLOEXEC);
	if (red_type == 2)
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0664);
	if (red_type == 3)
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND | O_CLOEXEC, 0664);
	if (fd == -1)
	{
		printf("%s: No such file or directory\n", filename);
		fd = -4242;
	}
	return (fd);
}
