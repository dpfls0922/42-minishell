/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 01:23:46 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/27 01:25:49 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	has_quotes(char *value)
{
	int	i;

	i = 0;
	while (value && value[i])
	{
		if (value[i] == '\"' || value[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	is_quotes(int i, int *quotes_index, int quotes_len)
{
	int	idx;

	idx = 0;
	while (idx < quotes_len)
	{
		if (quotes_index[idx] == i)
			return (1);
		idx++;
	}
	return (0);
}

int	get_quotes_len(char *cmd)
{
	int	i;
	int	double_flag;
	int	single_flag;
	int	len;

	i = 0;
	double_flag = 0;
	single_flag = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' && single_flag == 0)
		{
			len++;
			double_flag = !double_flag;
		}
		if (cmd[i] == '\'' && double_flag == 0)
		{
			len++;
			single_flag = !single_flag;
		}
		i++;
	}
	return (len);
}

int	*set_quotes_index(int *index, char *cmd)
{
	int	i;
	int	len;
	int	double_flag;
	int	single_flag;

	i = -1;
	len = 0;
	double_flag = 0;
	single_flag = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '"' && single_flag == 0)
		{
			index[len++] = i;
			double_flag = !double_flag;
		}
		if (cmd[i] == '\'' && double_flag == 0)
		{
			index[len++] = i;
			single_flag = !single_flag;
		}
	}
	return (index);
}

int	*get_quotes_index(char *s)
{
	int		*index;

	index = NULL;
	index = malloc (sizeof(int) * get_quotes_len(s));
	if (!index)
		exit (1);
	index = set_quotes_index(index, s);
	return (index);
}
