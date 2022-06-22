/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_envar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 03:42:46 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/21 17:00:58 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
*/
void	do_expand(t_expand_tools *exp_tools)
{
	char	*new_line;
	int		k;

	exp_tools->i = 0;
	exp_tools->s = -1;
	k = 0;
	new_line = (char *)malloc((exp_tools->new_exp_len + 1) * sizeof(char));
	while (++exp_tools->s < ft_strlen(exp_tools->main->first_split[exp_tools->index]))
	{
		if (exp_tools->main->env_index[exp_tools->index][k] == exp_tools->s)
		{
			exp_tools->e = -1;
			if (exp_tools->env_info[k].env_value != NULL)
			{
				while (++exp_tools->e < ft_strlen(exp_tools->env_info[k].env_value))
					new_line[exp_tools->i++] = exp_tools->env_info[k].env_value[exp_tools->e];
			}
			// printf("1 which env %d, ind-s %d, line-ind %d\n", k, exp_tools->s, exp_tools->i);
			exp_tools->s += (exp_tools->env_info[k].name_len - 1);
			k++;
		}
		else
		{
			if (exp_tools->env_info[k].e_valid != 3)
				new_line[exp_tools->i++] = exp_tools->main->first_split[exp_tools->index][exp_tools->s];
			// printf("2 which env %d, ind-s %d, line-ind %d\n", k, exp_tools->s, exp_tools->i);
		}
	}
	new_line[exp_tools->i] = '\0';
	free(exp_tools->main->first_split[exp_tools->index]);
	exp_tools->main->first_split[exp_tools->index] = ft_strdup(new_line);
	free(new_line);
	printf ("(%s)\n", exp_tools->main->first_split[exp_tools->index]);
}
