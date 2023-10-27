/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:27:17 by spark2            #+#    #+#             */
/*   Updated: 2023/10/27 21:45:39 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_data *data)
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

void	pwd(t_arg arg)
{
	char	*buf;

	buf = getcwd(0, 4096); //buf 사이즈 수정?
	write(arg.outfile, buf, ft_strlen(buf));
	write(arg.outfile, "\n", 1);
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

void	echo(char **line)
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

void	cd(char *path)
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

// char	**export(t_arg arg, char **envp, char **line)
// {
// 	int		i;
// 	char	**tmp;

// 	i = 0;
// 	if (!line[1]) //export 뒤 인자가 없다면 env 그냥 출력
// 	{
// 		while (envp[i])
// 		{
// 			write(arg.outfile, envp[i], ft_strlen(envp[i]));
// 			write(arg.outfile, "\n", 1);
// 			i++;
// 		}
// 	}
// 	else //export 뒤 인자 존재한다면 envp에 삽입
// 	{
// 		if ((line[1][0] >= '0' && line[1][0] <= '9') || line[1][0] == '=')//유효하지 않은 인자일 시 에러
// 		{
// 			write(arg.outfile, "export: ", 8);
// 			write(arg.outfile, "'", 1);
// 			write(arg.outfile, line[1], ft_strlen(line[1]));
// 			write(arg.outfile, "': ", 3);
// 			write(arg.outfile, "not a valid identifier\n", 23);
// 			return (envp);
// 		}
// 		tmp = envp;
// 		envp = ft_strjoin_2d(tmp, line[1]); //envp free?
// 		printf("debug !\n");
// 	}
// 	return (envp);
// }

void	unset(char **envp)
{
	(void)envp;
}

void	check_builtins(char **line, t_data *data)
{
	char	*builtin;

	builtin = line[0];
	if (!ft_strncmp(builtin, "env", 4))
		env(data);
	else if (!ft_strncmp(builtin, "pwd", 4))
		pwd(*arg);
	// else if (!ft_strncmp(builtin, "echo", 5))
	// 	echo(line);
	// else if (!ft_strncmp(builtin, "cd", 3))
	// 	cd(line[1]);
	// else if (!ft_strncmp(builtin, "export", 7))
	// 	export(*arg, envp, line);


	// if (!ft_strncmp(builtin, "unset", 6))
	// 	unset(envp);
	// int i = -1;
	// while (envp[++i])
	// 	printf("envp: %s\n", envp[i]);
}
