/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_envar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:14:20 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/23 14:55:28 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	init_exp_loop(t_expand_tools *exp_tools)
{
	exp_tools->i = 0;
	exp_tools->i_s = -1;
	exp_tools->pos = 0;
}

void	do_expand(t_expand_tools *exp_tools)
{
	char	*new_line;

	init_exp_loop(exp_tools);
	new_line = (char *)malloc((exp_tools->new_exp_len + 1) * sizeof(char));
	while (++exp_tools->i_s < ft_strlen(exp_tools->main->first_split[exp_tools->index]))
	{
		if (exp_tools->main->env_index[exp_tools->index][exp_tools->pos] == exp_tools->i_s)
		{
			exp_tools->i_e = -1;
			if (exp_tools->env_info[exp_tools->pos].env_value != NULL)
			{
				while (++exp_tools->i_e < ft_strlen(exp_tools->env_info[exp_tools->pos].env_value))
					new_line[exp_tools->i++] = exp_tools->env_info[exp_tools->pos].env_value[exp_tools->i_e];
			}
			exp_tools->i_s += (exp_tools->env_info[exp_tools->pos].name_len - 1);
			exp_tools->pos++;
		}
		else
			new_line[exp_tools->i++] = exp_tools->main->first_split[exp_tools->index][exp_tools->i_s];
	}
	new_line[exp_tools->i] = '\0';
	free(exp_tools->main->first_split[exp_tools->index]);
	exp_tools->main->first_split[exp_tools->index] = ft_strdup(new_line);
	free(new_line);
	printf ("(%s)\n", exp_tools->main->first_split[exp_tools->index]);
}