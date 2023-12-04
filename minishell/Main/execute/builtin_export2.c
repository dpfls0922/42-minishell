/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:12:17 by yerilee           #+#    #+#             */
/*   Updated: 2023/12/04 23:12:18 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**convert_env_list_to_export(t_env *node)
{
	int		i;
	char	*temp;
	char	**env;

	i = 0;
	env = (char **)malloc(sizeof(char *) * (get_env_list_size(node)) + 1);
	if (!env)
		return (NULL);
	while (node)
	{
		temp = ft_strdup(node->key);
		if (node->val)
		{
			temp = ft_strjoin(temp, "=\"");
			temp = ft_strjoin(temp, node->val);
			temp = ft_strjoin(temp, "\"");
		}
		env[i] = temp;
		node = node->next;
		i++;
	}
	env[i] = 0;
	return (env);
}

int	check_env_exist(t_env *env, char *str)
{
	int		equal_idx;
	t_env	*curr;

	equal_idx = ft_strchr_idx(str, '=');
	curr = env;
	while (curr)
	{
		if (!env || !env->val)
			return (-2);
		if (equal_idx == -1
			&& !ft_strncmp_equal(curr->key, str, ft_strlen(str)))
			return (0);
		else if (!ft_strncmp_equal(curr->key, str, equal_idx))
			return (ft_strlen(str) - 1);
		curr = curr->next;
	}
	return (-1);
}

void	modify_env_value(t_data *data, char *str)
{
	t_env	*cur_env;
	char	*new_key;
	int		equal_idx;

	cur_env = data->env_list;
	equal_idx = ft_strchr_idx(str, '=');
	if (equal_idx != -1)
		new_key = ft_strndup(str, equal_idx);
	else
		new_key = ft_strdup(str);
	while (cur_env)
	{
		if (!ft_strcmp_exec(cur_env->key, new_key))
			break ;
		cur_env = cur_env->next;
	}
	ft_free_str(new_key);
	if (equal_idx != -1)
	{
		if (cur_env->val)
			ft_free_str(cur_env->val);
		cur_env->val = ft_strdup(str + equal_idx + 1);
	}
	g_exit_status = 0;
}

void	add_env(t_data *data, char *str)
{
	t_env	*cur_env;
	t_env	*new_node;

	cur_env = data->env_list;
	while (cur_env)
	{
		if (cur_env->next == NULL)
			break ;
		cur_env = cur_env->next;
	}
	new_node = new_env_node_no_value(str);
	cur_env->next = new_node;
	new_node->prev = cur_env;
	g_exit_status = 0;
}
