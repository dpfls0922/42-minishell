/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujin <sujin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:47:03 by yerilee           #+#    #+#             */
/*   Updated: 2023/12/04 01:48:10 by sujin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(t_data *data, char **line)
{
	t_env	*curr;

	curr = data->env_list;
	if (line[1])
		no_such_file_error("env", line[1], 127, 0);
	if (!curr || !curr->val)
	{
		printf("env: No such file or directory\n");
		g_exit_status = 127;
		return ;
	}
	while (curr)
	{
		if (!curr->val)
			break ;
		else
			printf("%s=%s\n", curr->key, curr->val);
		curr = curr->next;
	}
}

// char	*get_minishell_env(char *env_val, t_env *env_list)
// {
// 	t_env	*curr;
// 	char	*pwd;

// 	curr = env_list;
// 	pwd = NULL;
// 	while (curr)
// 	{
// 		if (!ft_strcmp(env_val, curr->val))
// 		{
// 			pwd = ft_substr(curr->val, 0, ft_strlen(curr->val));
// 			break ;
// 		}
// 		else
// 			curr = curr->next;
// 	}
// 	return (pwd);
// }

void	builtin_pwd(t_data *data)
{
	char	*buf;

	(void)data;
	buf = getcwd(0, 4096);
	if (!buf)
	{
		printf("%s\n", buf);
		return ;	
	}
	write(data->cmd_list->fd_out, buf, ft_strlen(buf));
	write(data->cmd_list->fd_out, "\n", 1);
	free(buf);
	// if (buf == NULL)
	// {
	// 	buf = get_minishell_env("PWD", data->env_list);
	// 	if (!buf)
	// 		buf = getenv("PWD");
	// 	write(data->cmd_list->fd_out, buf, ft_strlen(buf));
	// 	write(data->cmd_list->fd_out, "\n", 1);
	// }
	// else
	// {
	// 	write(data->cmd_list->fd_out, buf, ft_strlen(buf));
	// 	write(data->cmd_list->fd_out, "\n", 1);
	// 	free(buf);
	// }
}

int	check_option_n(char *token)
{
	int	i;

	if (ft_strncmp_exec(token, "-n", 2))
		return (0);
	i = 2;
	while (token[i])
	{
		if (token[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	builtin_echo(t_cmd *cmd, int fd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (cmd->cmd[i] && check_option_n(cmd->cmd[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd->cmd[i])
	{
		write(fd, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (new_line)
		write(fd, "\n", 1);
}

int		check_env_home_exist(t_env *env_list)
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

void	builtin_cd(t_data *data, char *path)
{
	char	**old_pwd_export_2d;
	char	**curr_pwd_export_2d;
	char	*arg_exist_flag;

	arg_exist_flag = getcwd(0, 4096);
	if (arg_exist_flag)
		old_pwd_export_2d = make_pwd("OLDPWD=", arg_exist_flag);
	else
		old_pwd_export_2d = make_pwd("OLDPWD=", get_minishell_env_key("PWD", data->env_list));
	if (!path)
	{
		if (check_env_home_exist(data->env_list))
			chdir(getenv("HOME"));
		else
		{
			printf("cd: HOME not set\n");
			g_exit_status = 1;
			return ;
		}
	}
	else if (path[0] == '~')
	{
		if (!ft_strncmp_exec(path, "~", 2))
			chdir(getenv("HOME"));
		else if (path[1] == '/')
		{
			chdir(getenv("HOME"));
			if (path[2])
				if (chdir(path) == -1)
				{
					no_such_file_error("cd", path, 1, 0);
					return ;
				}
		}
		else
			ft_error("No such file or directory\n");
	}
	else if (path[0] == '-')
		chdir(get_minishell_env_key("OLDPWD", data->env_list));
	else
		if (chdir(path) == -1)
		{
			no_such_file_error("cd", path, 1, 0);
			return ;
		}		
	curr_pwd_export_2d = make_pwd("PWD=", getcwd(0, 4096));
	builtin_export(data, old_pwd_export_2d);
	builtin_export(data, curr_pwd_export_2d);
	ft_free_list(old_pwd_export_2d);
	ft_free_list(curr_pwd_export_2d);
}

void	builtin_exit(char **line)
{
	int	exit_code;

	printf("exit\n");
	if (!line[1])
		exit(0);
	else
	{
		exit_code = ft_atoi(line[1]);
		if (exit_code == -1)
		{
			printf("exit: %s: numeric argument required\n", line[1]);
			exit (255);
		}
		if (line[2])
			ft_error("exit: too many arguments\n");
		else
			exit(exit_code);
	}
}

int	is_builtin(t_cmd *cmd, t_data *data)
{
	int		fd;
	char	*builtin;

	builtin = cmd->cmd[0];
	if (!data->cmd_list->cmd[0] && cmd->heredoc_num)
		return (2);
	if (data->pipe_flag != 0)
		fd = 1;
	else
		fd = cmd->fd_out;
	if (!ft_strncmp_exec(builtin, "env", 4))
		builtin_env(data, cmd->cmd);
	else if (!ft_strncmp_exec(builtin, "pwd", 4))
		builtin_pwd(data);
	else if (!ft_strncmp_exec(builtin, "echo", 5))
		builtin_echo(cmd, fd);
	else if (!ft_strncmp_exec(builtin, "cd", 3))
		builtin_cd(data, cmd->cmd[1]);
	else if (!ft_strncmp_exec(builtin, "export", 7))
		builtin_export(data, cmd->cmd);
	else if (!ft_strncmp_exec(builtin, "exit", 5))
		builtin_exit(cmd->cmd);
	else if (!ft_strncmp_exec(builtin, "unset", 6))
		builtin_unset(data, cmd->cmd);
	else
		return (0);
	return (1);
}
