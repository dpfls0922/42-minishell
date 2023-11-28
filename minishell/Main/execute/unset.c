/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:11:35 by spark2            #+#    #+#             */
/*   Updated: 2023/11/28 17:46:01 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(t_env *node)
{
	if (node)
	{
		if (node->key)
		{
			free(node->key);
			node->key = 0;
		}
		if (node->val)
		{
			free(node->val);
			node->val = 0;
		}
		free(node);
	}
}

void    remove_env(t_data *data, char *remove_str)
{
    t_env   *curr;

	if (!ft_strcmp_exec(data->env_list->key, remove_str))
    {
        curr = data->env_list;
        data->env_list = data->env_list->next;
        free_node(curr);
        return;
    }
    curr = data->env_list;
    while (curr)
    {
        if (!ft_strcmp_exec(curr->key, remove_str))
            break ;
        curr = curr->next;
    }
    if (!curr)
        return ;
    if (curr->prev)
        curr->prev->next = curr->next;
    if (curr->next)
        curr->next->prev = curr->prev;
    free_node(curr);
}

void	builtin_unset(t_data *data, char **str)
{
	int	i;

	if (!data->cmd_list->cmd[1])
		return ;
	i = 0;
	while (str[++i])
	{
		if (!check_valid_arg(str[i]))
			continue ;
		if (!data->env_list)
		{
			printf("env: No such file or directory\n");
			g_exit_status = 127;
			break ;
		}
		remove_env(data, str[i]);
	}
}
