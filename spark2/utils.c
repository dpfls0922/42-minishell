/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:21:38 by spark2            #+#    #+#             */
/*   Updated: 2023/10/27 19:34:04 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_strjoin_2d(char **s1, char *s2)
{
	int		len;
	int		i;
	int		j;
	char	**str;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	len = i + 1;
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (0);
	str[i] = malloc(sizeof(char) * (ft_strlen(s2) + 1));
	i = 0;
	while (*s1)
	{
		str[i] = ft_strdup(*s1++);
		i++;
	}
	while (*s2)
	{
		str[i][j] = *s2++;
		j++;
	}
	str[i][j] = 0;
	str[i] = 0;
	return (str);
}
