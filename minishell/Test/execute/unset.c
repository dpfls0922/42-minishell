/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:11:35 by spark2            #+#    #+#             */
/*   Updated: 2023/11/27 19:46:35 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(t_env *node)
{
	free(node->key);
	node->key = 0;
	if (node->val)
	{
		free(node->val);
		node->val = 0;
	}
}

void	remove_env(t_env *env, char *remove_str)
{
	t_env	*cur_node;
	t_env	*prev_node;
	t_env	*next_node;

	cur_node = env;
	while (cur_node)
	{
		if (!ft_strcmp_exec(cur_node->key, remove_str))
			break ;
		cur_node = cur_node->next;
	}
	if (cur_node->prev)
	{
		prev_node = cur_node->prev;
		prev_node->next = cur_node->next;
	}
	if (cur_node->next)
	{
		next_node = cur_node->next;
		next_node->prev = cur_node->prev;
	}
	free_node(cur_node);
}

void	builtin_unset(t_env *env, char **str)
{
	int	i;
	int	env_idx;

	i = 0;
	while (str[++i])
	{
		if (!check_valid_arg(str[i]))
			continue ;
		env_idx = check_env_exist(env, str[i]);
		if (env_idx == -2)
		{
			printf("env: No such file or directory\n");
			g_exit_status = 127;
			break ;
		}
		if (env_idx != -1)
			remove_env(env, str[i]);
	}
}
