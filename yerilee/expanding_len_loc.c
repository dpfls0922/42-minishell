/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_len_loc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 23:02:00 by marvin            #+#    #+#             */
/*   Updated: 2023/10/23 23:02:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	len_before_env(char *value, int *len)
{
	int	double_flag;
	int	single_flag;

	double_flag = 0;
	single_flag = 0;
	while (single_flag == 1 || (value[*len] && value[*len] != '$'))
	{
		if (value[*len] == '\"' && single_flag == 0)
			double_flag = !double_flag;
		if (value[*len] == '\'' && double_flag == 0)
			single_flag = !single_flag;
		*len++;
	}
	return (*len);
}

int	len_after_env(char *value)
{
	int	len;
	int	i;
	int	double_flag;
	int	single_flag;

	double_flag = 0;
	single_flag = 0;
	i = 0;
	len = 0;
	while (single_flag == 1 || (value[i] && value[i] != '$'))
	{
		if (value[i] == '\"' && single_flag == 0)
			double_flag = !double_flag;
		if (value[i] == '\'' && double_flag == 0)
			single_flag = !single_flag;
		i++;
	}
	if (value[i] && value[i] == '$')
	{
        i++;
        i = location_after_env(i, value);
		while (value[i++])
			len++;
	}
	return (len);
}

int	location_after_env(int i, char *value)
{
	while (value[i] && (is_alnum(value[i]) || value[i] == '_'))
		i++;
	return (i);
}
