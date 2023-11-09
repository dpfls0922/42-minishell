/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:46:41 by spark2            #+#    #+#             */
/*   Updated: 2023/11/09 22:22:10 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_exist(t_env *env, char *str)
{
	int		equal_idx;
	t_env	*curr;

	equal_idx = ft_strchr_idx(str, '=');
	curr = env;
	while (curr)
	{
		if (!ft_strncmp_equal(curr->key, str, equal_idx)) //env에 key 있음, '=' 있음 (export abcde abcd 처리 해야 함 !!)
			return (equal_idx);
		else if (equal_idx == -1 && ft_strncmp_equal(curr->key, str, ft_strlen(str)) == 0) //key 있음, '=' 없음 (ex: export abc)
			return (ft_strlen(str) - 1);
		curr = curr->next;
	}
	return (-1); //env에 key 없음
}

void	modify_env_value(t_data *data, char *str, int equal_idx)
{
	t_env	*cur_env;
	char	*new_key;
	char	*new_val;

	cur_env = data->env_list;
	new_key = ft_strndup(str, equal_idx);
	while (cur_env)
	{
		if (!ft_strcmp(cur_env->key, new_key))
			break ;
		cur_env = cur_env->next;
	}
	cur_env->key = new_key; ///
	equal_idx = ft_strchr_idx(str, '=');
	if (equal_idx != -1) //key O, '=' x, value x
	{
		new_val = ft_strdup(str + equal_idx + 1);
		cur_env->val = new_val;
	}
}

t_env	*new_env_node_no_value(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit(1);
	node->key = ft_strdup(str);
	node->val = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_env(t_data *data, char *str)
{
	t_env	*cur_env;
	t_env	*new_node;
	int		equal_idx;

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
	equal_idx = ft_strchr_idx(str, '=');
	// new_node->key = ft_strndup(str, equal_idx);
	// new_node->val = ft_strdup(str + equal_idx + 1);
}

void	builtin_export(t_data *data, char **line)
{
	int		i;
	int		equal_idx;

	i = 0;
	if (!line[1]) //export 뒤 인자가 없다면 env 그냥 출력
	//value 없으면 export는 출력 O, env는 출력 X
		builtin_env(data);
	else //export 뒤 인자 존재한다면 envp에 삽입
	{
		while (line[++i])
		{
			equal_idx = check_env_exist(data->env_list, line[i]);
			if ((line[i][0] >= '0' && line[i][0] <= '9') || line[i][0] == '='
				|| line[i][0] == '?' || line[i][0] == '/')//유효하지 않은 인자일 시 에러
			{
				write(data->cmd_list->fd_out, "export: ", 8);
				write(data->cmd_list->fd_out, "'", 1);
				write(data->cmd_list->fd_out, line[i], ft_strlen(line[i]));
				write(data->cmd_list->fd_out, "': ", 3);
				write(data->cmd_list->fd_out, "not a valid identifier\n", 23);
			}
			else if (equal_idx != -1) //이미 존재하는 key라면 -> value 수정
				modify_env_value(data, line[i], equal_idx);
			else //존재하지 않는 key라면 -> export에 새로 key, value 추가
				add_env(data, line[i]);
		}
	}
}
