/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:32:58 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:32:58 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	is_valid_env(t_data *data, char *var)
{
	t_env	*curr;

	curr = data->env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->key, var))
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	is_alnum(int c)
{
	if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		|| ((c >= '0') && (c <= '9')))
		return (1);
	else
		return (0);
}

char	*find_env(char *str, int *i)
{
	char	*env;
	int		start;
	int		index;

	index = *i + 1;
	start = *i + 1;
	while (str[index])
	{
		if (is_alnum(str[index]) || str[index] == '_')
			index++;
		else
		{
			index--;
			break ;
		}
	}
	*i = index;
	env = ft_substr(str, start, index - start + 1);
	return (env);
}

char	*get_value(t_data *data, char *key)
{
	t_env	*curr;

	curr = data->env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			return (curr->val);
		curr = curr->next;
	}
	return (NULL);
}
