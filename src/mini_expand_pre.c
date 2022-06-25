/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_pre.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:11:56 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/24 14:51:52 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	find_istart(t_env_info *env_info)
{
	char	c;

	c = env_info->exp_tools->main->first_split[env_info->exp_tools->index][env_info->e_index + 1];
	if (c == ' ' || c == '\t' || c == '\v' || c == 34 || c == 39 || c == '\0' || c == ':' || c == '=')
		env_info->i_start = env_info->e_index;
	else
		env_info->i_start = env_info->e_index + 1;
}

void	find_name_size(t_env_info *env_info)
{
	int	i;

	i = env_info->i_start;
	while (++i < ft_strlen(env_info->exp_tools->main->first_split[env_info->exp_tools->index]))
	{
		if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\t')
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\v')
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == ' ')
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\0')
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == 34)
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == 39)
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '$')
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '=')
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == ':')
			break ;
	}
	env_info->i_end = i - 1;
	env_info->name_len = (env_info->i_end - env_info->i_start) + 1;
}

/*
	// if (env_info->e_valid != 0)
*/
void	handle_1dollar_case(t_env_info *env_info)
{
	char	*line;

	line = ft_strdup \
	(env_info->exp_tools->main->first_split[env_info->exp_tools->index]);
	if (line[env_info->e_index + 1] == '\0' || \
		line[env_info->e_index + 1] == '\v' || \
		(line[env_info->e_index - 1] == '\v' && \
		line[env_info->e_index + 1] == '\v') || \
		line[env_info->e_index + 1] == ' ' || \
		line[env_info->e_index + 1] == '\t' || \
		line[env_info->e_index + 1] == ':' || \
		line[env_info->e_index + 1] == '=' || \
		line[env_info->e_index + 1] == 34 || \
		line[env_info->e_index + 1] == 39 || \
		(line[env_info->e_index - 1] == 34 && \
		line[env_info->e_index + 1] == 34))
	{
		env_info->env_value = (char *)malloc(sizeof(char) * 2);
		env_info->env_value[0] = '$';
		env_info->env_value[1] = '\0';
		env_info->value_len = 1;
		env_info->name_len = 1;
		env_info->i_end = env_info->e_index;
	}
}

/*
	// printf("old exp len %d\n", env_info->exp_tools->new_exp_len);
	// printf("old line %s\n", exp_tools->main->first_split[exp_tools->index]);
*/
void	init_env_info(t_env_info *env_info, t_expand_tools *exp_tools, int i)
{
	env_info->exp_tools = exp_tools;
	env_info->e_pos = i;
	env_info->e_index = exp_tools->main->env_index[exp_tools->index][i];
	env_info->e_valid = exp_tools->main->exp_valid[exp_tools->index][i];
	env_info->i_start = env_info->e_index + 1;
	find_istart(env_info);
	find_name_size(env_info);
	if (env_info->e_valid == 0 || !find_env(env_info))
		env_info->env_ptr = NULL;
	get_env_value(env_info);
	env_info->name_len++;
	handle_1dollar_case(env_info);
}
