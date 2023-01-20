/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_pre.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:11:56 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

void	find_istart(t_env_info *env_info)
{
	char	c;

	c = env_info->exp_tools->main->first_split[env_info->exp_tools->index] \
	[env_info->e_index + 1];
	if (c == ' ' || c == '\t' || c == '\v' || c == 34 || c == 39 || c == '\0' \
	|| c == ':' || c == '=' || c == '/' || c == '$')
		env_info->i_start = env_info->e_index;
	else
		env_info->i_start = env_info->e_index + 1;
	if (c == '?')
		env_info->status_var = 1;
}

int	name_ending(char end)
{
	if (end == '\t' || end == '\v' || end == ' ' || end == '\0' || \
	end == 34 || end == 39 || end == '$' || end == '=' || \
	end == ':' || end == '/')
		return (1);
	return (0);
}

void	find_name_size(t_env_info *env_info)
{
	int	i;

	i = env_info->i_start;
	while (++i < ft_strlen(env_info->exp_tools->main->first_split \
	[env_info->exp_tools->index]))
	{
		if (name_ending(env_info->exp_tools->main->first_split \
		[env_info->exp_tools->index][i]))
			break ;
	}
	if (env_info->status_var)
	{
		env_info->i_end = env_info->i_start;
		env_info->name_len = 1;
	}
	else
	{
		env_info->i_end = i - 1;
		env_info->name_len = (env_info->i_end - env_info->i_start) + 1;
	}
}

void	check_e_status(t_env_info *env_info)
{
	char	*line;
	int		i;

	line = ft_strdup(env_info->exp_tools->main->first_split \
	[env_info->exp_tools->index]);
	i = -1;
	while (++i < ft_strlen(line))
	{
		if (i == env_info->i_start)
		{
			if (i == env_info->i_end)
			{
				if (line[i] == '?')
					env_info->e_valid = 'e';
			}
		}
	}
	free(line);
}

/*
	// printf("old exp len %d\n", env_info->exp_tools->new_exp_len);
	// printf("old line %s\n", exp_tools->main->first_split[exp_tools->index]);
*/
void	init_env_info(t_env_info *env_info, t_expand_tools *exp_tools, int i)
{
	env_info->env_value = NULL;
	env_info->exp_tools = exp_tools;
	env_info->e_pos = i;
	env_info->e_index = exp_tools->main->env_index[exp_tools->index][i];
	env_info->e_valid = exp_tools->main->exp_valid[exp_tools->index][i];
	env_info->i_start = env_info->e_index + 1;
	env_info->i_end = 0;
	env_info->value_len = 0;
	env_info->status_var = 0;
	find_istart(env_info);
	find_name_size(env_info);
	if (env_info->e_valid == 0 || !find_env(env_info))
		env_info->env_ptr = NULL;
	check_e_status(env_info);
	get_env_value(env_info);
	env_info->name_len++;
	handle_1dollar_case(env_info);
}
