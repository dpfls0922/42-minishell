/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:46:41 by spark2            #+#    #+#             */
/*   Updated: 2023/11/29 17:32:42 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sorting_ascending_order(t_env *env)
{
	t_env	*curr;
	int		j;
	int		cnt;

	j = 1;
	cnt = 0;
	curr = env;
	while (curr)
	{
		cnt++;
		curr = curr->next;
	}
	while (j < cnt)
	{
		curr = env;
		while (curr->next)
		{
			if (ft_strcmp(curr->key, curr->next->key) > 0)
				ft_swap(&(curr->key), &(curr->next->key));
			curr = curr->next;
		}
		j++;
	}
}

int	get_env_list_size(t_env *node)
{
	int	count;

	count = 0;
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}

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
		temp = 0;
		i++;
	}
	env[i] = 0;
	return (env);
}

void	print_export(t_data *data)
{
	int		i;
	int		j;
	char	**splited_key1;
	char	**splited_key2;
	char	**env_strs;

	i = -1;
	env_strs = convert_env_list_to_export(data->env_list);
	while (env_strs[++i])
	{
		j = -1;
		while (env_strs[++j + 1])
		{
			splited_key1 = ft_split(env_strs[j], '=');
			splited_key2 = ft_split(env_strs[j + 1], '=');
			if (ft_strcmp(splited_key1[0], splited_key2[0]) > 0)
				ft_swap(&env_strs[j], &env_strs[j + 1]);
		}
	}
	i = 0;
	while (env_strs[i])
		ft_printf("declare -x %s\n", env_strs[i++]);
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
			return (-2); //env 자체가 없을 경우
		if (equal_idx == -1
			&& !ft_strncmp_equal(curr->key, str, ft_strlen(str)))
			return (0); //str에 '='가 없으며, key가 env에 존재
		else if (!ft_strncmp_equal(curr->key, str, equal_idx))
			return (ft_strlen(str) - 1);
		curr = curr->next; //str에 '=' 존재, key가 env에 존재
	}
	return (-1); //env에 찾고자 하는 key 없음
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
	g_exit_status = 0;
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
	g_exit_status = 0;
}

int	check_valid_arg(char *str)
{
	if (((str[0] >= '0' && str[0] <= '9') || str[0] == '='
		|| str[0] == '?' || str[0] == '/') || !ft_strcmp(str, "") || !ft_strcmp(str, " "))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_exit_status = 1;
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
