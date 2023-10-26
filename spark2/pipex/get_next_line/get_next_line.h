/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:52:12 by spark2            #+#    #+#             */
/*   Updated: 2023/10/03 17:34:35 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

int		main_loop(char **backup, int fd, ssize_t *rd_size);
int		split_line(char **backup, char **res);
void	ft_free_gnl(char **backup, char **res);
char	*get_next_line(int fd);
int		ft_strncmp_gnl(const char *s1, const char *s2, size_t n);
size_t	ft_strlen_gnl(const char *str);
ssize_t	ft_strchr_gnl(const char *s, int c);
char	*ft_substr(char const *s, size_t start, size_t len);
char	*ft_strdup(const char *src);
char	*ft_strjoin_gnl(char *s1, char const *s2);

#endif