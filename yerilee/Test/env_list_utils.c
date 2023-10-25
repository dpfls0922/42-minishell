/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:32:48 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:32:48 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_env	*new_env_node(char *str)
{
	t_env	*node;
	int		i;

	node = malloc(sizeof(t_env));
	if (!node)
		exit(1);
	i = 0;
	while (str[i] != '=')
		i++;
	node->key = ft_substr(str, 0, i);
	i++;
	if (str[i])
		node->val = ft_substr(str, i, ft_strlen(str) - i);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_env	*add_env_to_list(t_env *env, char *str)
{
	t_env	*node;
	t_env	*curr;

	if (!str)
		return (NULL);
	node = new_env_node(str);
	if (!node)
		exit(1);
	if (!env)
		return (node);
	curr = env;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = node;
	node->prev = curr;
	return (env);
}
