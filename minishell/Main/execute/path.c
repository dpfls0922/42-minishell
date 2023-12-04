/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:23:06 by spark2            #+#    #+#             */
/*   Updated: 2023/12/04 18:32:18 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_path_envp(t_cmd *cmd, char **envp)
{
	while (ft_strncmp_exec("PATH", *envp, 4))
		envp++;
	cmd->path = ft_split(*envp + 5, ':');
}

void	check_slash_exist(char	*cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK))
			no_such_file_error("", cmd, 127, 1);
		is_a_dir_error(cmd);
	}
	else
		cmd_not_found_error(cmd);
}

char	*check_valid_path(char **path, char *path_cmd, char *tmp)
{
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
	return (0);
}

char	*get_cmd_path(char **path, char *cmd)
{
	char	*tmp;
	char	*path_cmd;

	tmp = 0;
	if (access(cmd, X_OK) == 0)
	{
		if (opendir(cmd))
			is_a_dir_error(cmd);
		return (ft_strdup(cmd));
	}
	if (!ft_strcmp(cmd, ""))
		cmd_not_found_error(cmd);
	path_cmd = ft_strjoin_exec("/", cmd);
	tmp = check_valid_path(path, path_cmd, tmp);
	if (tmp)
		return (tmp);
	free(path_cmd);
	check_slash_exist(cmd);
	return (NULL);
}
