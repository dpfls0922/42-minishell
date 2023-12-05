/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command_split.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:06:01 by yerilee           #+#    #+#             */
/*   Updated: 2023/12/05 17:48:02 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

size_t	word_count(char *s, char c)
{
	int	i;
	int	count;
	int	d_flag;
	int	s_flag;

	d_flag = 0;
	s_flag = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"' && s_flag == 0)
			d_flag = !d_flag;
		if (s[i] == '\'' && d_flag == 0)
			s_flag = !s_flag;
		if (d_flag == 0 && s_flag == 0
			&& (s[i] != c && (!s[i + 1] || s[i + 1] == c)))
			count++;
		i++;
	}
	return (count);
}

void	word_len(t_split *split, char c, int flag)
{
	if (c == '"' && split->s_flag == 0)
	{
		split->len++;
		split->d_flag = !split->d_flag;
		return ;
	}
	if (c == '\'' && split->d_flag == 0)
	{
		split->len++;
		split->s_flag = !split->s_flag;
		return ;
	}
	if (flag)
		split->len++;
}

char	**ft_free_word(char	**p, int i)
{
	while (i >= 0)
	{
		free(p[i]);
		i--;
	}
	free(p);
	return (p);
}

int	ft_free_list(char **p)
{
	int	i;

	i = 0;
	while (p && p[i])
	{
		free(p[i]);
		p[i] = 0;
		i++;
	}
	if (p)
	{
		free(p);
		p = 0;
	}
	return (0);
}

char	**split_command(char *s, char c)
{
	int		i;
	t_split	split;

	i = 0;
	init_split(&split, s, c);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		split.len = 0;
		word_len(&split, *s, 0);
		while ((s[split.len] && ((split.d_flag == 1 || split.s_flag == 1)))
			|| (s[split.len] && s[split.len] != c))
			word_len(&split, s[split.len], 1);
		if (split.len)
		{
			split.p[i] = ft_substr(s, 0, split.len);
			if (!split.p[i])
				ft_free_word(split.p, i);
			i++;
		}
		s = s + split.len;
	}
	split.p[i] = NULL;
	return (split.p);
}
