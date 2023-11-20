/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:02:01 by yerilee           #+#    #+#             */
/*   Updated: 2023/11/17 21:49:30 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	count_heredoc(t_data *data, t_lexer *lexer)
{
	while (lexer)
	{
		if (!ft_strcmp(lexer->val, "<<"))
			data->heredoc_num++;
		lexer = lexer->next;
	}
}

void	handle_heredoc(t_data *data, t_lexer *lexer)
{
	int	i;

	i = 0;
	count_heredoc(data, lexer);
	if (data->heredoc_num)
	{
		data->end = malloc(sizeof(char *) * (data->heredoc_num + 1));
		if (!data->end)
			exit (1);
		lexer = data->lexer_list;
		while (lexer)
		{
			if (ft_strcmp(lexer->val, "<<") == 0)
			{
				lexer = lexer->next;
				data->end[i] = ft_substr(lexer->val, 0, ft_strlen(lexer->val));
				data->end[i] = delete_quotes_in_str(data->end[i]);
				i++;
			}
			lexer = lexer->next;
		}
		data->end[i] = NULL;
	}
}

char	**get_new_command(t_cmd *cmd)
{
	int		token_num;
	int		i;
	int		j;
	char	**new_cmd;

	token_num = 1;
	new_cmd = NULL;
	while (cmd->cmd && cmd->cmd[token_num])
		token_num++;
	new_cmd = malloc(sizeof(char *) * (token_num - cmd->heredoc_num * 2 + 1));
	if (!new_cmd)
		exit (1);
	i = 0;
	j = 0;
	while (cmd->cmd && cmd->cmd[i])
	{
		if (ft_strcmp(cmd->cmd[i], "<<") == 0)
			i++;
		else
			new_cmd[j++] = ft_substr(cmd->cmd[i], 0, ft_strlen(cmd->cmd[i]));
		i++;
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}

char	**replace_with_new_command(char **new, char **cmd)
{
	int	i;

	i = 0;
	while (new && new[i])
	{
		cmd[i] = ft_substr(new[i], 0, ft_strlen(new[i]));
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	delete_heredoc(t_cmd *node)
{
	int		i;
	char	**new_cmd;

	if (node && node->heredoc_num)
	{
		new_cmd = get_new_command(node);
		i = 0;
		while (new_cmd && new_cmd[i])
			i++;
		ft_free_list(node->cmd);
		node->cmd = malloc (sizeof(char *) * (i + 1));
		if (!node->cmd)
			exit (1);
		node->cmd = replace_with_new_command(new_cmd, node->cmd);
		ft_free_list(new_cmd);
	}
}
