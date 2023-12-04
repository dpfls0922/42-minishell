/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:19:26 by spark2            #+#    #+#             */
/*   Updated: 2023/12/04 18:19:27 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_data *data)
{
	int		i;
	int		j;
	char	**splited_key1;
	char	**splited_key2;
	char	**env_strs;

	i = -1;
	env_strs = convert_env_list_to_export(data->env_list);
	while (env_strs[++i])
	{
		j = -1;
		while (env_strs[++j + 1])
		{
			splited_key1 = ft_split(env_strs[j], '=');
			splited_key2 = ft_split(env_strs[j + 1], '=');
			if (ft_strcmp(splited_key1[0], splited_key2[0]) > 0)
				ft_swap(&env_strs[j], &env_strs[j + 1]);
		}
	}
	i = 0;
	while (env_strs[i])
		ft_printf("declare -x %s\n", env_strs[i++]);
}

void	builtin_export(t_data *data, char **line)
{
	int		i;
	int		equal_idx;

	i = 0;
	if (!line[1])
		print_export(data);
	else
	{
		while (line[++i])
		{
			equal_idx = check_env_exist(data->env_list, line[i]);
			if (!check_valid_arg("export", line[i]))
				;
			else if (equal_idx != -1)
				modify_env_value(data, line[i]);
			else
				add_env(data, line[i]);
		}
	}
}
