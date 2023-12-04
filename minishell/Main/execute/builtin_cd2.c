/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:56:08 by spark2            #+#    #+#             */
/*   Updated: 2023/12/04 22:32:57 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env_home_exist(t_env *env_list)
{
	t_env	*curr;

	curr = env_list;
	while (curr)
	{
		if (!ft_strcmp("HOME", curr->key))
			return (1);
		curr = curr->next;
	}
	return (0);
}

char	*get_minishell_env_key(char *env_key, t_env *env_list)
{
	t_env	*curr;
	char	*pwd;

	curr = env_list;
	pwd = NULL;
	while (curr)
	{
		if (!ft_strcmp(env_key, curr->key))
		{
			pwd = ft_substr(curr->val, 0, ft_strlen(curr->val));
			break ;
		}
		else
			curr = curr->next;
	}
	return (pwd);
}

char	**make_pwd(char *str, char *arg_exist_flag)
{
	char	*pwd;
	char	*pwd_export;
	char	**pwd_export_2d;
	char	*malloc_str;

	pwd = ft_strdup(arg_exist_flag);
	malloc_str = ft_strdup(str);
	pwd_export = ft_strjoin(malloc_str, pwd);
	pwd_export_2d = malloc(sizeof(char *) * 3);
	pwd_export_2d[0] = ft_strdup("export");
	pwd_export_2d[1] = ft_strdup(pwd_export);
	pwd_export_2d[2] = 0;
	ft_free_str(pwd);
	ft_free_str(pwd_export);
	return (pwd_export_2d);
}

int	cd_none_path(t_data *data)
{
	if (check_env_home_exist(data->env_list))
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else
	{
		printf("cd: HOME not set\n");
		g_exit_status = 1;
		return (0);
	}
}

int	cd_wave_path(char *path)
{
	if (!ft_strncmp_exec(path, "~", 2))
		return (chdir(getenv("HOME")));
	else if (path[1] == '/')
	{
		chdir(getenv("HOME"));
		if (path[2])
		{
			if (chdir(path) == -1)
			{
				no_such_file_error("cd", path, 1, 0);
				return (0);
			}
		}
	}
	else
	{
		ft_error("No such file or directory\n");
		return (1);
	}
	return (1);
}
