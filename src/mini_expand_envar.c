/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_envar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 03:42:46 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/07 01:41:53 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	loop_init(t_env_expand *exp_tools, int op)
{
	if (op == 1)
	{
		if (exp_tools->e != -1)
			exp_tools->e = -1;
	}
	if (op == 2)
	{
		exp_tools->e = -1;
		exp_tools->s += (exp_tools->name_len + 1);
	}
	if (op == 3)
	{
		if (exp_tools->e != -1)
			exp_tools->i--;
	}
}
/*
	// i = -1;
	// while (++i < exp_tools->new_len_exp)
	// 	printf("new_line %c, i%d\n", new_line[i], i);
	// printf("1check %c, i%d, k%d\n", new_line[i], i, k);
	// printf("2check %c, i%d, k%d\n", new_line[i], i, k);
*/	
void	do_expand(t_env_expand *exp_tools)
{
	char	*new_line;

	// printf("%d do_expand(exp_tools)\n", exp_tools->new_len_exp);
	new_line = (char *)malloc(exp_tools->new_len_exp * sizeof(char) + 1);
	while (++exp_tools->i < exp_tools->new_len_exp)
	{
		loop_init(exp_tools, 1);
		if (exp_tools->main->first_split[exp_tools->index][exp_tools->s] != '$')
			new_line[exp_tools->i] = exp_tools->main->first_split[exp_tools->index][exp_tools->s++];
		else if (exp_tools->main->first_split[exp_tools->index][exp_tools->s] == '$')
		{
			loop_init(exp_tools, 2);
			while (++exp_tools->e < ft_strlen(exp_tools->env_ptr->env_cont))
				new_line[exp_tools->i++] = exp_tools->env_ptr->env_cont[exp_tools->e];
		}
		loop_init(exp_tools, 3);
	}
	new_line[exp_tools->i] = '\0';
	free (exp_tools->main->first_split[exp_tools->index]);
	exp_tools->main->first_split[exp_tools->index] = ft_strdup(new_line);
	free (new_line);
	// printf("new_line %s\n", exp_tools->main->first_split[exp_tools->index]);
}
