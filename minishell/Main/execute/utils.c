/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:21:38 by spark2            #+#    #+#             */
/*   Updated: 2023/12/04 16:51:49 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *src, int n)
{
	int		i;
	char	*dst;

	i = 0;
	dst = (char *)malloc(sizeof(char) * (n + 1));
	if (!dst)
		return (0);
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
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
