/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:28:10 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/16 17:25:59 by yerilee          ###   ########.fr       */
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

	if (!token)
		return (NULL);
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

t_lexer	*add_token_in_lexer(t_lexer *lexer, char *token, int type)
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
	data->lexer_list = add_token_in_lexer(data->lexer_list, token, PIPE);
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
	data->lexer_list = add_token_in_lexer(data->lexer_list, token, AMPERSAND);
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
	data->lexer_list = add_token_in_lexer(data->lexer_list, token, SEMICOLON);
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
	data->lexer_list = add_token_in_lexer(data->lexer_list, token, REDIRECTION);
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
	data->lexer_list = add_token_in_lexer(data->lexer_list, token, PARENTHESIS);
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
	data->lexer_list = add_token_in_lexer(data->lexer_list, token, WORD);
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
		if (data->cmd[i] != '|' && data->cmd[i] != '&'
			&& !is_redirection(data->cmd[i]))
			i = add_word(data, i);
	}
	free(data->cmd);
}

int	init_data(t_data *data, int argc, char **env)
{
	data->ac = argc;
	if (env && env[0])
		data->env = env;
	return (1);
}

int	minishell(t_data *data)
{
	while (1)
	{
		data->cmd = readline("minishell $ ");
		if (!data->cmd)
			break ;
		else if (!*data->cmd)
			free(data->cmd);
		else if (data->cmd && data->cmd[0] != '\0')
		{
			lexer(data);
			// syntax analyzer
			// check_syntax(data);
			// parser
			// execution
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	if (!init_data(&data, argc, env))
		exit(1);
	if (!minishell(&data))
		return (0);
}
