/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:19:24 by yerilee           #+#    #+#             */
/*   Updated: 2023/12/05 17:03:58 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*allocate_new_val(char *prev_exit, char *value)
{
	int		len;
	char	*new;

	len = ft_strlen(prev_exit) + ft_strlen(value) - 2;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	return (new);
}

char	*change_exit_status(t_data *data, char *value)
{
	t_exit	exit;

	init_exit(data, &exit, value);
	while (exit.value[exit.i])
	{
		if (exit.value[exit.i] == '\"' && exit.s_flag == 0)
			exit.d_flag = !exit.d_flag;
		if (exit.value[exit.i] == '\'' && exit.d_flag == 0)
			exit.s_flag = !exit.s_flag;
		if (exit.s_flag == 0 && exit.value[exit.i] == '$'
			&& exit.value[exit.i + 1] == '?')
		{
			exit.new_val[exit.j] = '\0';
			exit.new_val = ft_strjoin(exit.new_val, exit.prev_exit);
			exit.j += ft_strlen(exit.prev_exit);
			exit.i += 2;
		}
		else
			exit.new_val[exit.j++] = exit.value[exit.i++];
	}
	free(exit.prev_exit);
	exit.new_val[exit.j] = '\0';
	return (exit.new_val);
}

void	ft_change(t_data *data, t_lexer *curr)
{
	char	*temp;

	temp = change_exit_status(data, curr->val);
	free(curr->val);
	curr->val = temp;
}

void	handle_exit_status(t_data *data)
{
	int		i;
	int		double_flag;
	int		single_flag;
	t_lexer	*curr;

	double_flag = 0;
	single_flag = 0;
	curr = data->lexer_list;
	while (curr)
	{
		i = 0;
		while (curr->val[i])
		{
			if (curr->val[i] == '\"' && single_flag == 0)
				double_flag = !double_flag;
			if (curr->val[i] == '\'' && double_flag == 0)
				single_flag = !single_flag;
			if (single_flag == 0
				&& curr->val[i] == '$' && curr->val[i + 1] == '?')
				ft_change(data, curr);
			i++;
		}
		curr = curr->next;
	}
}
