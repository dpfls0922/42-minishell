/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:23:06 by spark2            #+#    #+#             */
/*   Updated: 2023/11/22 21:37:09 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_path_envp(t_cmd *cmd, char **envp)
{
	while (ft_strncmp_exec("PATH", *envp, 4))
		envp++;
	cmd->path = ft_split(*envp + 5, ':');
}

char	*get_cmd_path(char **path, char *cmd)
{
	char	*path_cmd;
	char	*tmp;

	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	path_cmd = ft_strjoin_exec("/", cmd);
	while (*path)
	{
		tmp = ft_strjoin_exec(*path, path_cmd);
		if (!access(tmp, X_OK))
		{
			free(path_cmd);
			return (tmp);
		}
		free(tmp);
		path++;
	}
	free(path_cmd);
	if (!access(cmd, F_OK))
		print_error("permission denied\n");
	if (ft_strchr(cmd, '/'))
		no_such_file_error(cmd, 1);
	else
		cmd_not_found_error(cmd);
	return (NULL);
}
