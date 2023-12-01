/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_no_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:50:06 by spark2            #+#    #+#             */
/*   Updated: 2023/12/01 19:22:01 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_no_free(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strndup(s2, ft_strlen(s2)));
	if (!s2)
		return (ft_strndup(s1, ft_strlen(s1)));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result_str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!result_str)
		return (NULL);
	result_str[s1_len] = 0;
	ft_strlcpy(result_str, s1, s1_len + 1);
	ft_strlcpy(result_str + s1_len, (char *)s2, s2_len + 1);
	return (result_str);
}
