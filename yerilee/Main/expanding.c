/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:33:18 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:33:18 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	has_variable(char *value)
{
	int		i;
	int		double_flag;
	int		single_flag;

	i = 0;
	double_flag = 0;
	single_flag = 0;
	while (value && value[i])
	{
		if (value[i] == '\"' && single_flag == 0)
			double_flag = !double_flag;
		if (value[i] == '\'' && double_flag == 0)
			single_flag = !single_flag;
		if (single_flag == 0 && value[i] == '$'
			&& value[i + 1]
			&& (is_alnum(value[i + 1]) || value[i + 1] == '_'))
			return (1);
		i++;
	}
	return (0);
}

int	has_variable_in_lexer(t_data *data)
{
	t_lexer	*curr;

	curr = data->lexer_list;
	while (curr)
	{
		if (!ft_strcmp(curr->val, "<<"))
		{
			curr = curr->next;
			if (curr->next)
				curr = curr->next;
		}
		if (has_variable(curr->val))
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	expanding(t_data *data)
{
	int		flag;
	t_lexer	*curr;

	curr = data->lexer_list;
	while (curr && has_variable_in_lexer(data))
	{
		flag = 0;
		curr = data->lexer_list;
		while (curr)
		{
			if (!ft_strcmp(curr->val, "<<"))
			{
				curr = curr->next;
				if (curr->next)
					curr = curr->next;
				else
					flag = 1;
			}
			if (curr && curr->type == WORD && has_variable(curr->val)
				&& flag != 1)
				ft_expanding(data, curr);
			curr = curr->next;
		}
	}
}

void	ft_expanding(t_data *data, t_lexer *lexer)
{
	int		i;
	char	*replaced_val;
	char	*env;

	i = 0;
	env = NULL;
	replaced_val = ft_substr(lexer->val, 0, len_before_env(lexer->val, &i));
	if (lexer->val[i] && lexer->val[i + 1])
		env = find_env(lexer->val, &i);
	if (env)
	{
		if (is_valid_env(data, env))
		{
			replaced_val = ft_strjoin(replaced_val, get_value(data, env));
			replaced_val = strjoin_after_env(replaced_val, i, lexer->val);
		}
		else
			replaced_val = str_without_env(lexer->val, replaced_val);
		free(lexer->val);
		lexer->val = replaced_val;
		free(env);
	}
}
