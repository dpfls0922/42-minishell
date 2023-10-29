/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:38:55 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/29 19:33:05 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	has_quotes(char *value)
{
	int	i;

	i = 0;
	while (value && value[i])
	{
		if (value[i] == '\"' || value[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*get_new_string(char *s, int position)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc(sizeof(char) * ft_strlen(s));
	if (!new_str)
		exit (1);
	i = 0;
	j = 0;
	// printf("s[i] : %c\n", s[position]);
	while (s && s[i])
	{
		if (i != position)
			new_str[j++] = s[i];
		// printf("new_str[%d] : %c\n", j - 1, new_str[j - 1]);
		i++;
	}
	new_str[j] = 0;
	return (new_str);
}

char	*ft_delete_quotes(char *s, int i, int double_flag, int single_flag)
{
	char	*temp;
	char	*new_str;

	new_str = NULL;
	temp = ft_substr(s, 0, ft_strlen(s));
	while (temp && temp[i])
	{
		if (temp[i] == '\"' && single_flag == 0)
		{
			double_flag = !double_flag;
			new_str = get_new_string(temp, i);
			free(temp);
			temp = ft_substr(new_str, 0, ft_strlen(new_str));
			printf("i : %d, new_str : %s\n", i, new_str);
		}
		if (temp[i] == '\'' && double_flag == 0)
		{
			single_flag = !single_flag;
			new_str = get_new_string(temp, i);
			free(temp);
			temp = ft_substr(new_str, 0, ft_strlen(new_str));
			printf("i : %d, new_str : %s\n", i, new_str);
		}
		i++;
	}
	free(temp);
	return (new_str);
}

char	*delete_quotes_in_str(char *str)
{
	char	*old;
	char	*new;

	old = NULL;
	if (has_quotes(str))
	{
		old = ft_substr(str, 0, ft_strlen(str));
		// printf("old : %s\n", old);
		new = ft_delete_quotes(old, 0, 0, 0);
		// printf("new : %s\n", new);
		str = ft_substr(new, 0, ft_strlen(new));
		free(old);
		free(new);
	}
	return (str);
}

void	delete_quotes_in_list(t_cmd *cmd_list)
{
	int		i;
	t_cmd	*curr;

	curr = cmd_list;
	while (curr && curr->cmd)
	{
		i = 0;
		while (curr->cmd[i])
		{
			delete_quotes_in_str(curr->cmd[i]);
			i++;
		}
		curr = curr->next;
	}
}
