/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:23:49 by spark2            #+#    #+#             */
/*   Updated: 2023/03/19 17:32:51 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free(char **ptr, int i)
{
	while (i >= 0)
		free(ptr[i--]);
	free(ptr);
	return (0);
}

int	cnt_word(const char *s, char c)
{
	int	word;

	word = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			word++;
		while (*s && *s != c)
			s++;
	}
	return (word);
}

char	*ft_word_dup(const char *src, char c)
{
	int		i;
	char	*dst;

	i = 0;
	while (src[i] && src[i] != c)
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (0);
	i = 0;
	while (src[i] && src[i] != c)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**ptr;

	i = 0;
	j = 0;
	ptr = malloc(sizeof(char *) * (cnt_word(s, c) + 1));
	if (!ptr)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			ptr[j] = ft_word_dup(&s[i], c);
			if (!ptr[j++])
				return (ft_free(ptr, j - 2));
		}
		while (s[i] && s[i] != c)
			i++;
	}
	ptr[j] = 0;
	return (ptr);
}
