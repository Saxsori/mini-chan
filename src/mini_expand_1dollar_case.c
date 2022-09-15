/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_1dollar_case.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:51:17 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/15 01:33:26 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	take_1dollar_val(t_env_info *env_info)
{
	env_info->env_value = (char *)malloc(sizeof(char) * 2);
	env_info->env_value[0] = '$';
	env_info->env_value[1] = '\0';
	env_info->value_len = 1;
	env_info->name_len = 1;
	env_info->i_end = env_info->e_index;
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
		line[env_info->e_index + 1] == '/' || \
		line[env_info->e_index + 1] == 34 || \
		line[env_info->e_index + 1] == 39 || \
		(line[env_info->e_index - 1] == 34 && \
		line[env_info->e_index + 1] == 34) || \
		line[env_info->e_index + 1] == '$' || \
		(line[env_info->e_index - 1] == '$' && \
		line[env_info->e_index + 1] == '$'))
		take_1dollar_val(env_info);
	free(line);
}
