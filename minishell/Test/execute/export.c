/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:46:41 by spark2            #+#    #+#             */
/*   Updated: 2023/11/14 20:42:00 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (equal_idx == -1 && !ft_strncmp_equal(curr->key, str, ft_strlen(str))) //key 있음, '=' 없음
			return (0);
		else if (!ft_strncmp_equal(curr->key, str, equal_idx)) //env에 key 있음, '=' 있음
			return (ft_strlen(str) - 1);
		curr = curr->next;
	}
	return (-1); //env에 key 없음
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
	if (equal_idx != -1) //key O, '=' x, value x
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
	if (equal_idx == -1) //'=' 없음
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
	while (cur_env) //마지막 노드까지 이동
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
	if (!line[1]) //export 뒤 인자가 없다면 env 그냥 출력
		print_export(data);
	else //export 뒤 인자 존재한다면 envp에 삽입
	{
		while (line[++i])
		{
			equal_idx = check_env_exist(data->env_list, line[i]);
			if (!check_valid_arg(line[i]))
				;
			else if (equal_idx != -1) //이미 존재하는 key라면 -> value 수정
				modify_env_value(data, line[i]);
			else //존재하지 않는 key라면 -> export에 새로 key, value 추가
				add_env(data, line[i]);
		}
	}
}
