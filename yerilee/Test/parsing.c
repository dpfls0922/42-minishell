/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:27:26 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/27 16:39:08 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	get_fd_in(int *fd, int *red_type, int red_num)
{
	int	fd_in;
	int	i;

	fd_in = 0;
	i = 0;
	while (i < red_num)
	{
		if (red_type[i] == 1)
			fd_in = fd[i];
		i++;
	}
	return (fd_in);
}

int	get_fd_out(int *fd, int *red_type, int red_num)
{
	int	fd_out;
	int	i;

	fd_out = 1;
	i = 0;
	while (i < red_num)
	{
		if (red_type[i] == 2 || red_type[i] == 3)
			fd_out = fd[i];
		i++;
	}
	return (fd_out);
}

char	*set_command(t_data *data)
{
	char	*command;
	t_lexer	*curr;

	command = NULL;
	curr = data->lexer_list;
	while (curr && curr->type != PIPE)
	{
		command = ft_strjoin(command, curr->val);
		command = ft_strjoin(command, " ");
		curr = curr->next;
	}
	return (command);
}

size_t	word_count(char *s, char c)
{
	int	i;
	int	count;
	int	d_flag;
	int	s_flag;

	d_flag = 0;
	s_flag = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"' && s_flag == 0)
			d_flag = !d_flag;
		if (s[i] == '\'' && d_flag == 0)
			s_flag = !s_flag;
		if (d_flag == 0 && s_flag == 0
			&& (s[i] != c && (!s[i + 1] || s[i + 1] == c)))
			count++;
		i++;
	}
	return (count);
}

void	word_len(t_split *split, char c, int flag)
{
	if (c == '"' && split->s_flag == 0)
	{
		split->len++;
		split->d_flag = !split->d_flag;
		return ;
	}
	if (c == '\'' && split->d_flag == 0)
	{
		split->len++;
		split->s_flag = !split->s_flag;
		return ;
	}
	if (flag)
		split->len++;
}

void	init_split(t_split *split, char *s, char c)
{
	split->len = 0;
	split->d_flag = 0;
	split->s_flag = 0;
	if (!s)
		return ;
	split->p = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!split->p)
		return ;
}

char	**ft_free_word(char	**p, int i)
{
	while (i >= 0)
	{
		free(p[i]);
		i--;
	}
	free(p);
	return (p);
}

char	**split_command(char *s, char c)
{
	int		i;
	t_split	split;

	i = 0;
	init_split(&split, s, c);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		split.len = 0;
		word_len(&split, *s, 0);
		while ((s[split.len] && ((split.d_flag == 1 || split.s_flag == 1)))
			|| (s[split.len] && s[split.len] != c))
			word_len(&split, s[split.len], 1);
		if (split.len)
		{
			split.p[i] = ft_substr(s, 0, split.len);
			if (!split.p[i])
				ft_free_word(split.p, i);
			i++;
		}
		s = s + split.len;
	}
	split.p[i] = NULL;
	return (split.p);
}

t_cmd	*new_command_node(char *command, int fd_in, int fd_out)
{
	int		i;
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		exit (1);
	cmd->cmd = split_command(command, ' ');
	cmd->fd_in = fd_in;
	cmd->fd_out = fd_out;
	cmd->heredoc_num = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	i = 0;
	while (cmd->cmd && cmd->cmd[i])
	{
		if (ft_strcmp(cmd->cmd[i], "<<") == 0)
			cmd->heredoc_num++;
		i++;
	}
	printf("cmd->heredoc_num : %d\n", cmd->heredoc_num);
	return (cmd);
}

t_cmd	*add_command_to_list(t_data *data, int *fd, int *red_type, int red_num)
{
	int		fd_in;
	int		fd_out;
	t_cmd	*node;
	t_cmd	*curr;
	char	*command;

	fd_in = get_fd_in(fd, red_type, red_num);
	fd_out = get_fd_out(fd, red_type, red_num);
	free(fd);
	free(red_type);
	command = set_command(data);
	printf("fd_in : %d, fd_out : %d, command : %s\n", fd_in, fd_out, command);
	node = new_command_node(command, fd_in, fd_out);
	free(command);
	if (!data->cmd_list)
		return (node);
	curr = data->cmd_list;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = node;
	node->prev = curr;
	return (data->cmd_list);
}

void	print_command_list(t_cmd *cmd_list)
{
	int		i;
	t_cmd	*curr;

	curr = cmd_list;
	while (curr)
	{
		i = 0;
		while (curr->cmd && curr->cmd[i])
		{
			printf("cmd : %s\n", curr->cmd[i]);
			i++;
		}	
		curr = curr->next;
	}
}

void	make_command_list(t_data *data, int red_num, int *red_type)
{
	int		*fd;
	char	*filename;
	int		i;
	t_lexer	*curr;

	filename = NULL;
	fd = malloc(sizeof(int) * red_num);
	if (!fd)
		exit (1);
	i = 0;
	curr = data->lexer_list;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == REDIRECTION && ft_strcmp(curr->val, "<<"))
		{
			curr = curr->next;
			filename = get_file_name(curr->val);
			fd[i] = set_fd(filename, red_type[i]);
			i++;
			free(filename);
		}
		curr = curr->next;
	}
	// printf("red_num : %d\n", red_num);
	// printf("red_type : %d\n", red_type[0]);
	// printf("fd : %d\n", fd[0]);
	// printf("filename : %s\n", filename);

	// redirection 지우기
	// delete_redirection(data);
	data->cmd_list = add_command_to_list(data, fd, red_type, red_num);
	print_command_list(data->cmd_list);
}

void	handle_command(t_data *data)
{
	int	red_num;
	int	*red_type;

	red_num = get_red_num(data);
	red_type = set_red_type(data, red_num);
	make_command_list(data, red_num, red_type);
}

/* $? 처리 -> heredoc 처리 -> command_list 만들기 -> quotes 제거 */
void	parsing(t_data *data)
{
	t_lexer	*lexer;

	lexer = data->lexer_list;
	// $? 처리
	handle_heredoc(data, lexer);
	handle_command(data);
	// quotes 제거
}
