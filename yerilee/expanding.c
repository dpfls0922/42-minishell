/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:33:18 by yerilee           #+#    #+#             */
/*   Updated: 2023/10/24 16:33:18 by yerilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// double_flag, single_flag를 변수 선언하지 않고, 구조체 변수로 두고 이를 확인할 것
int	has_variable(char *value)
{
	int		i;
	int		double_flag;
	int		single_flag;

	i = 0;
	double_flag = 0;
	single_flag = 0;
	while (value && value[i])
	{
		if (value[i] == '\"' && single_flag == 0)
			double_flag = !double_flag;
		if (value[i] == '\'' && double_flag == 0)
			single_flag = !single_flag;
		if (single_flag == 0 && value[i] == '$'
			&& value[i + 1]
			&& (is_alnum(value[i + 1]) || value[i + 1] == '_'))
			return (1);
		i++;
	}
	return (0);
}

// 달러가 있을 동안 expanding 실행할 조건 추가하기
void	expanding(t_data *data)
{
	t_lexer	*curr;

	curr = data->lexer_list;
	while (curr)
	{
		if (curr->type == WORD && has_variable(curr->val))
			ft_expanding(data, curr);
		curr = curr->next;
	}
}

/*
ft_expanding : 주어진 입력 문자열(lexer->val)에서 환경 변수를 찾아 해당 환경 변수를 실제 값으로 치환하여 새로운 문자열을 생성하는 함수
1. lexer->val의 처음부터 환경 변수가 시작하는 위치까지(substring)의 문자열로 초기화
2. 환경 변수의 확장이 필요한 경우(즉, env 변수가 NULL이 아닌 경우), replaced_val 변수에 환경 변수가 확장된 결과를 join함
3. 이후 문자열도 join하여, 최종적으로 replaced_val 변수에는 환경 변수가 확장된 결과 문자열이 저장됨
*/

void	ft_expanding(t_data *data, t_lexer *lexer)
{
	int		i;
	char	*replaced_val;
	char	*env;

	i = 0;
	env = NULL;
	replaced_val = ft_substr(lexer->val, 0, len_before_env(lexer->val, &i));
	if (lexer->val[i] && lexer->val[i + 1])
		env = find_env(lexer->val, &i);
	if (env)
	{
		if (is_valid_env(data, env))
		{
			replaced_val = ft_strjoin(replaced_val, get_value(data, env));
			replaced_val = strjoin_after_env(replaced_val, i, lexer->val);
		}
		else
			replaced_val = str_without_env(lexer->val, replaced_val);
		free(lexer->val);
		lexer->val = replaced_val;
		free(env);
		free(replaced_val);
	}
}
