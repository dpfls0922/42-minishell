/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:12:28 by yerilee           #+#    #+#             */
/*   Updated: 2023/12/04 23:12:29 by yerilee          ###   ########.fr       */
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

void	remove_env(t_data *data, char *remove_str)
{
	t_env	*curr;

	if (!ft_strcmp_exec(data->env_list->key, remove_str))
	{
		curr = data->env_list;
		data->env_list = data->env_list->next;
		free_node(curr);
		return ;
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

int	check_valid_arg(char *cmd, char *str)
{
	int	i;
	int	equal_idx;

	i = 0;
	equal_idx = ft_strchr_idx(str, '=');
	if (equal_idx == 0)
		return (print_export_unset_error(cmd, str));
	if (equal_idx == -1)
		equal_idx = ft_strlen(str) - 1;
	while (i <= equal_idx && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (print_export_unset_error(cmd, str));
		i++;
	}
	if (((str[0] >= '0' && str[0] <= '9') || str[0] == '='
			|| str[0] == '?' || str[0] == '/') || !ft_strcmp(str, "")
	)
		return (print_export_unset_error(cmd, str));
	else
		return (1);
}

void	builtin_unset(t_data *data, char **str)
{
	int	i;

	if (!data->cmd_list->cmd[1])
		return ;
	i = 0;
	while (str[++i])
	{
		if (!check_valid_arg("unset", str[i]))
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
