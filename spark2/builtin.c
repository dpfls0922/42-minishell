/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujin <sujin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:27:17 by spark2            #+#    #+#             */
/*   Updated: 2023/11/04 20:27:12 by sujin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_data *data)
{
	t_env	*curr;

	curr = data->env_list;
	while (curr)
	{
		write(data->cmd_list->fd_out, curr->key, ft_strlen(curr->key));
		write(data->cmd_list->fd_out, curr->val, ft_strlen(curr->val));
		write(data->cmd_list->fd_out, "\n", 1);
		curr = curr->next;
	}
}

void	builtin_pwd(t_data *data)
{
	char	*buf;

	buf = getcwd(0, 4096); //buf 사이즈 수정?
	// printf("buf: %s\n", buf);
	write(data->cmd_list->fd_out, buf, ft_strlen(buf));
	write(data->cmd_list->fd_out, "\n", 1);
	free(buf);
}

int	check_option_n(char *token)
{
	int	i;

	if (ft_strncmp(token, "-n", 2))
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

void	builtin_echo(char **line)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (line[i] && check_option_n(line[i]))
	{
		new_line = 0;
		i++;
	}
	while (line[i])
	{
		write(1, line[i], ft_strlen(line[i]));
		if (line[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}

void	builtin_cd(char *path) //홈 디렉토리가 env에서 제거되었을 경우 처리 필요
{
	if (!path)
		chdir(getenv("HOME"));
	else if (path[0] == '~')
	{
		if (!ft_strncmp(path, "~", 2))
			chdir(getenv("HOME"));
		else if (path[1] == '/')
		{
			chdir(getenv("HOME"));
			if (path[2])
				if (chdir(path) == -1)
					ft_error("No such file or directory\n");
		}
		else
			ft_error("No such file or directory\n");
	}
	else
		if (chdir(path) == -1)
			ft_error("No such file or directory\n");
}

void	modify_env_value(t_data *data, char *str, int equal_idx)
{
	t_env	*curr_env;
	char	*new_key;
	char	*new_val;

	new_key = ft_strndup(str, equal_idx + 1);
	new_val = ft_strdup(str + equal_idx + 1);
	curr_env = data->env_list;
	while (curr_env)
	{
		if (ft_strncmp(curr_env->key, str, equal_idx))
			break ;
		curr_env = curr_env->next;
	}
	curr_env->key = new_key;
	curr_env->val = new_val;
}

int	check_env_exist(t_env *env, char *str)
{
	int		i;
	int		equal_idx;
	t_env	*curr;

	i = 0;
	equal_idx = -1;
	curr = env;
	if (ft_strchr(str, '=')) //str(key + value)에 '=' 존재
		equal_idx = i;
	while (curr)
	{
		if (!ft_strncmp(curr->key, str, equal_idx + 1)) //env에 key 존재 (export abcde abcd 처리 해야 함 !!!!!!!!)
			return (equal_idx);
		else if (equal_idx == -1 && ft_strncmp(curr->key, str, ft_strlen(str)) == 0) //key 있음, '=' 없음, value 없음 (ex: export abc)
			return (0);
		curr = curr->next;
	}
	return (-1);
}

void	builtin_export(t_data *data, char **line)
{
	int		i;
	int		equal_idx;

	i = 0;
	if (!line[1]) //export 뒤 인자가 없다면 env 그냥 출력
		builtin_env(data);
	else //export 뒤 인자 존재한다면 envp에 삽입
	{
		while (line[++i])
		{
			equal_idx = check_env_exist(data->env_list, line[i]);
			if ((line[i][0] >= '0' && line[i][0] <= '9') || line[i][0] == '='
				|| line[i][0] == '?' || line[i][0] == '/')//유효하지 않은 인자일 시 에러
			{
				write(data->cmd_list->fd_out, "export: ", 8);
				write(data->cmd_list->fd_out, "'", 1);
				write(data->cmd_list->fd_out, line[i], ft_strlen(line[i]));
				write(data->cmd_list->fd_out, "': ", 3);
				write(data->cmd_list->fd_out, "not a valid identifier\n", 23);
			}
			else if (equal_idx != -1) //이미 존재하는 key라면 -> value 수정
				modify_env_value(data, line[i], equal_idx);
			// else //존재하지 않는 key라면 -> export에 새로 key, value 추가
			// {

			// }
		}
	}
}

// void	builtin_unset(t_env *env);
// {
// 	(void)env;
// }

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

int	is_builtin(char **line, t_data *data)
{
	char	*builtin;

	builtin = line[0];
	if (!ft_strncmp(builtin, "env", 4))
		builtin_env(data);
	else if (!ft_strncmp(builtin, "pwd", 4))
		builtin_pwd(data);
	else if (!ft_strncmp(builtin, "echo", 5))
		builtin_echo(line);
	else if (!ft_strncmp(builtin, "cd", 3))
		builtin_cd(line[1]);
	else if (!ft_strncmp(builtin, "export", 7))
		builtin_export(data, line);
	else if (!ft_strncmp(builtin, "exit", 5))
		builtin_exit(line);
	// else if (!ft_strncmp(builtin, "unset", 6))
	// 	unset(data->env_list);
	else
		return (0);
	return (1);
}
