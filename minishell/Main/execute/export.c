/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:46:41 by spark2            #+#    #+#             */
/*   Updated: 2023/11/17 19:53:16 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_data *data)
{
	t_env	*curr;

	curr = data->env_list;
	while (curr)
	{
		if (!curr->val)
			printf("%s\n", curr->key);
		else
			printf("%s=\"%s\"\n", curr->key, curr->val);
		curr = curr->next;
	}
}

int	check_env_exist(t_env *env, char *str)
{
	int		equal_idx;
	t_env	*curr;

	equal_idx = ft_strchr_idx(str, '=');
	curr = env;
	while (curr)
	{
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
	free(new_key);
	if (equal_idx != -1)
	{
		if (cur_env->val)
			free(cur_env->val);
		cur_env->val = ft_strdup(str + equal_idx + 1);
	}
}

t_env	*new_env_node_no_value(char *str)
{
	int		equal_idx;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit(1);
	equal_idx = ft_strchr_idx(str, '=');
	if (equal_idx == -1)
	{
		node->key = ft_strdup(str);
		node->val = NULL;
	}
	else
	{
		node->key = ft_strndup(str, equal_idx);
		node->val = ft_strdup(str + equal_idx + 1);
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
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
}

int	check_valid_arg(char *str)
{
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '='
		|| str[0] == '?' || str[0] == '/')
	{
		printf("export: '%s': not a valid identifier\n", str);
		return (0);
	}
	else
		return (1);
}

void	builtin_export(t_data *data, char **line)
{
	int		i;
	int		equal_idx;

	i = 0;
	if (!line[1])
		print_export(data);
	else
	{
		while (line[++i])
		{
			equal_idx = check_env_exist(data->env_list, line[i]);
			if (!check_valid_arg(line[i]))
				;
			else if (equal_idx != -1)
				modify_env_value(data, line[i]);
			else
				add_env(data, line[i]);
		}
	}
}
