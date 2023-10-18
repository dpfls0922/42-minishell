/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:28:10 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/18 16:32:35 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == '\t' || c == '\n'
		|| c == '\r' || c == '\v'
		|| c == ' ' || c == '\f')
		return (1);
	return (0);
}

int	is_parenthesis(char c)
{
	if (c == '{' || c == '}'
		|| c == '(' || c == ')')
		return (1);
	return (0);
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_word(char c)
{
	if (c != '|' && c != '&' && c != ';'
		&& !is_space(c) && !is_redirection(c) && !is_parenthesis(c))
		return (1);
	return (0);
}

t_lexer	*new_lexer_node(char *token, int type)
{
	t_lexer	*node;
	int		i;

	node = malloc(sizeof(t_lexer));
	if (!node)
		exit(1);
	node->val = malloc(sizeof(char) * (ft_strlen(token) + 1));
	if (!node->val)
		exit(1);
	i = -1;
	while (token[++i])
		node->val[i] = token[i];
	node->val[i] = '\0';
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_lexer	*add_token_to_lexer(t_lexer *lexer, char *token, int type)
{
	t_lexer	*node;
	t_lexer	*curr;

	if (!token)
		return (NULL);
	node = new_lexer_node(token, type);
	if (!node)
		exit(1);
	if (!lexer)
		return (node);
	curr = lexer;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = node;
	node->prev = curr;
	return (lexer);
}

int	add_pipe(t_data *data, int i)
{
	int		start;
	int		len;
	char	*token;

	start = i;
	len = 0;
	while (data->cmd[i] && data->cmd[i] == '|')
	{
		i++;
		len++;
	}
	token = ft_substr(data->cmd, start, len);
	data->lexer_list = add_token_to_lexer(data->lexer_list, token, PIPE);
	free(token);
	token = NULL;
	return (i);
}

int	add_ampersand(t_data *data, int i)
{
	int		start;
	int		len;
	char	*token;

	start = i;
	len = 0;
	while (data->cmd[i] && data->cmd[i] == '&')
	{
		i++;
		len++;
	}
	token = ft_substr(data->cmd, start, len);
	data->lexer_list = add_token_to_lexer(data->lexer_list, token, AMPERSAND);
	free(token);
	token = NULL;
	return (i);
}

int	add_semicolon(t_data *data, int i)
{
	int		start;
	int		len;
	char	*token;

	start = i;
	len = 0;
	while (data->cmd[i] && data->cmd[i] == ';')
	{
		i++;
		len++;
	}
	token = ft_substr(data->cmd, start, len);
	data->lexer_list = add_token_to_lexer(data->lexer_list, token, SEMICOLON);
	free(token);
	token = NULL;
	return (i);
}

int	add_redirection(t_data *data, int i)
{
	int		start;
	int		len;
	char	*token;

	start = i;
	len = 0;
	while (data->cmd[i] && is_redirection(data->cmd[i]))
	{
		i++;
		len++;
	}
	token = ft_substr(data->cmd, start, len);
	data->lexer_list = add_token_to_lexer(data->lexer_list, token, REDIRECTION);
	free(token);
	token = NULL;
	return (i);
}

int	add_parenthesis(t_data *data, int i)
{
	int		start;
	int		len;
	char	*token;

	start = i;
	len = 0;
	while (data->cmd[i] && is_parenthesis(data->cmd[i]))
	{
		i++;
		len++;
	}
	token = ft_substr(data->cmd, start, len);
	data->lexer_list = add_token_to_lexer(data->lexer_list, token, PARENTHESIS);
	free(token);
	token = NULL;
	return (i);
}

int	ft_word_len(char *cmd, int i)
{
	int		len;
	char	quote;

	len = 0;
	while (cmd[i] && is_word(cmd[i]))
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			quote = cmd[i];
			i++;
			len++;
			while (cmd[i] && cmd[i] != quote)
			{
				i++;
				len++;
			}
		}
		i++;
		len++;
	}
	return (len);
}

int	add_word(t_data *data, int i)
{
	char	*token;

	token = ft_substr(data->cmd, i, ft_word_len(data->cmd, i));
	i += ft_word_len(data->cmd, i);
	data->lexer_list = add_token_to_lexer(data->lexer_list, token, WORD);
	free(token);
	token = NULL;
	return (i);
}

void	lexer(t_data *data)
{
	int		i;

	i = 0;
	data->cmd = ft_strtrim(data->cmd, " ");
	add_history(data->cmd);
	while (data->cmd[i])
	{
		while (is_space(data->cmd[i]))
			i++;
		if (data->cmd[i] == '|')
			i = add_pipe(data, i);
		if (data->cmd[i] == '&')
			i = add_ampersand(data, i);
		if (data->cmd[i] == ';')
			i = add_semicolon(data, i);
		if (is_redirection(data->cmd[i]))
			i = add_redirection(data, i);
		if (is_parenthesis(data->cmd[i]))
			i = add_parenthesis(data, i);
		if (data->cmd[i] && data->cmd[i] != '|' && data->cmd[i] != '&'
			&& !is_space(data->cmd[i]) && !is_redirection(data->cmd[i]))
			i = add_word(data, i);
	}
	free(data->cmd);
}

int	check_token_start(t_lexer *lexer)
{
	char	c;
	t_lexer	*curr;

	curr = lexer;
	if (curr->type == AMPERSAND || curr->type == PARENTHESIS
		|| curr->type == SEMICOLON)
	{
		c = curr->val[0];
		printf("Syntax error near unexpected token `%c'\n", c);
		return (1);
	}
	return (0);
}

int	check_closed_quote(int double_flag, int single_flag)
{
	if (double_flag || single_flag)
	{
		printf ("syntax error: unclosed quotation mark.\n");
		return (1);
	}
	return (0);
}

int	check_quotes(t_lexer *lexer)
{
	t_lexer	*curr;
	int		i;
	int		double_flag;
	int		single_flag;

	curr = lexer;
	double_flag = 0;
	single_flag = 0;
	while (curr)
	{
		if (curr->type == WORD)
		{
			i = 0;
			while (curr->val[i])
			{
				if (curr->val[i] == '\"' && (single_flag == 0))
					double_flag = !double_flag;
				if (curr->val[i] == '\'' && (double_flag == 0))
					single_flag = !single_flag;
				i++;
			}
		}
		curr = curr->next;
	}
	return (check_closed_quote(double_flag, single_flag));
}

int	check_pipe_start_end(t_lexer *lexer)
{
	int		flag;
	t_lexer	*curr;

	flag = 0;
	curr = lexer;
	if (curr->type == PIPE)
		flag = 1;
	while (curr->next)
		curr = curr->next;
	if (curr->type == PIPE)
		flag = 1;
	if (flag == 1)
	{
		printf("syntax error: near unexpected token `|'.\n");
		return (1);
	}
	return (0);
}

int	check_pipe_len(t_lexer *lexer)
{
	t_lexer	*curr;

	curr = lexer;
	while (curr)
	{
		if (curr->type == PIPE && ft_strlen(curr->val) > 1)
		{
			printf("syntax error near unexpected token `|'.\n");
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	check_command_between_pipes(t_lexer *lexer)
{
	t_lexer	*curr;
	int		cmd_num;

	curr = lexer;
	while (curr)
	{
		cmd_num = 0;
		if (curr->type == PIPE)
		{
			curr = curr->next;
			while (curr && curr->type != PIPE)
			{
				cmd_num++;
				curr = curr->next;
			}
			if (cmd_num == 0 && curr->type == PIPE)
			{
				printf("syntax error: near unexpected token `|'.\n");
				return (1);
			}
		}
		if (curr && curr->type != PIPE)
			curr = curr->next;
	}
	return (0);
}

int	check_pipe(t_lexer *lexer)
{
	if (check_pipe_start_end(lexer) || check_pipe_len(lexer)
		|| check_command_between_pipes(lexer))
		return (1);
	return (0);
}

int	check_redirection_end(t_lexer *lexer)
{
	t_lexer	*curr;

	curr = lexer;
	while (curr->next)
		curr = curr->next;
	if (curr->type == REDIRECTION)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	check_redirection_len(t_lexer *lexer)
{
	t_lexer	*curr;

	curr = lexer;
	while (curr)
	{
		if (curr->type == REDIRECTION && ft_strlen(curr->val) > 2)
		{
			printf("syntax error near unexpected token `%s'\n", curr->val);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	check_command_after_redirection(t_lexer *lexer)
{
	t_lexer	*curr;

	curr = lexer;
	while (curr)
	{
		if (curr->type == REDIRECTION)
		{
			curr = curr->next;
			if (curr->next && (curr->type == PIPE || curr->type == REDIRECTION))
			{
				printf("syntax error near unexpected token `%s'\n", curr->val);
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

int	check_redirection(t_lexer *lexer)
{
	if (check_redirection_end(lexer) || check_redirection_len(lexer)
		|| check_command_after_redirection(lexer))
		return (1);
	return (0);
}

int	check_syntax(t_lexer *lexer)
{
	if (!lexer)
		return (1);
	if (check_token_start(lexer) || check_quotes(lexer) || check_pipe(lexer)
		|| check_redirection(lexer))
		return (1);
	return (0);
}

int	init_data1(t_data *data, int argc, char **env)
{
	data->ac = argc;
	if (env && env[0])
		data->env = env;
	return (1);
}

void	init_data2(t_data *data)
{
	data->lexer_list = NULL;
}

void	ft_free_lexer(t_lexer *lexer)
{
	t_lexer	*curr;
	t_lexer	*next;

	curr = lexer;
	while (curr)
	{
		next = curr->next;
		free(curr->val);
		free(curr);
		curr = next;
	}
	// curr = NULL;
	// next = NULL;
}

int	minishell(t_data *data)
{
	while (1)
	{
		init_data2(data);
		data->cmd = readline("minishell $ ");
		if (!data->cmd)
			break ;
		else if (!*data->cmd)
			free(data->cmd);
		else if (data->cmd && data->cmd[0] != '\0')
		{
			lexer(data);
			if (check_syntax(data->lexer_list))
			{
				ft_free_lexer(data->lexer_list);
				continue ;
			}
			// parser
			// execution
		}
		rl_clear_history();
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	if (!init_data1(&data, argc, env))
		exit(1);
	if (!minishell(&data))
		return (0);
}
