/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:33:12 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:33:12 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*str_after_env(char *value)
{
	int		i;
	int		single_flag;
	int		double_flag;
	char	*after;

	i = 0;
	single_flag = 0;
	double_flag = 0;
	after = NULL;
	while (single_flag == 1 || (value[i] && value[i] != '$'))
	{
		if (value[i] == '\"' && single_flag == 0)
			double_flag = !double_flag;
		if (value[i] == '\'' && double_flag == 0)
			single_flag = !single_flag;
		i++;
	}
	if (value[i] && value[i] == '$' && single_flag == 0)
	{
		i++;
		i = location_after_env(i, value);
		if (value && value[i])
			after = ft_substr(value, i, len_after_env(value));
	}
	return (after);
}

char	*strjoin_after_env(char *replaced_str, int i, char *lexer)
{
	char	*after;

	i++;
	i = location_after_env(i, lexer);
	if (lexer[i])
	{
		after = ft_substr(lexer, i, ft_strlen(lexer) - i);
		replaced_str = ft_strjoin(replaced_str, after);
		free(after);
	}
	return (replaced_str);
}

char	*str_without_env(char *lexer, char *replaced_val)
{
	char	*after;

	after = str_after_env(lexer);
	replaced_val = ft_strjoin(replaced_val, after);
	free(after);
	return (replaced_val);
}
