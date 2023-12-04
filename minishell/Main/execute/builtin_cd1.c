/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:55:16 by spark2            #+#    #+#             */
/*   Updated: 2023/12/04 17:55:51 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**before_cd(t_data *data, char **old_pwd_export_2d)
{
	char	*arg_exist_flag;

	arg_exist_flag = getcwd(0, 4096);
	if (arg_exist_flag)
		old_pwd_export_2d = make_pwd("OLDPWD=", arg_exist_flag);
	else
		old_pwd_export_2d = make_pwd("OLDPWD=", \
		get_minishell_env_key("PWD", data->env_list));
	return (old_pwd_export_2d);
}

void	after_cd(t_data *data, char **old_pwd, char **curr_pwd)
{
	curr_pwd = make_pwd("PWD=", getcwd(0, 4096));
	builtin_export(data, old_pwd);
	builtin_export(data, curr_pwd);
	ft_free_list(old_pwd);
	ft_free_list(curr_pwd);
}

int	do_cd(t_data *data, char *path)
{
	if (!path)
	{
		if (!cd_none_path(data))
			return (0);
	}
	else if (path[0] == '~')
	{
		if (!cd_wave_path(path))
			return (0);
	}
	else if (path[0] == '-')
		return (chdir(get_minishell_env_key("OLDPWD", data->env_list)));
	else
	{
		if (chdir(path) == -1)
		{
			no_such_file_error("cd", path, 1, 0);
			return (0);
		}
	}
	return (1);
}

void	builtin_cd(t_data *data, char *path)
{
	char	**old_pwd_export_2d;
	char	**curr_pwd_export_2d;

	old_pwd_export_2d = 0;
	curr_pwd_export_2d = 0;
	old_pwd_export_2d = before_cd(data, old_pwd_export_2d);
	if (!do_cd(data, path))
		return ;
	after_cd(data, old_pwd_export_2d, curr_pwd_export_2d);
}
