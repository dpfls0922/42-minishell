/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:23:06 by spark2            #+#    #+#             */
/*   Updated: 2023/11/15 16:26:57 by yerilee          ###   ########.fr       */
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
	print_error("command not found\n");
	return (NULL);
}
