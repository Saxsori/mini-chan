/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_envar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 03:42:46 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/07 00:23:26 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"
	// i = -1;
	// while (++i < exp_tools->new_len_exp)
	// 	printf("new_line %c, i%d\n", new_line[i], i);
void	do_expand(t_env_expand *exp_tools)
{
	char	*new_line;
	int		i;
	int		k;
	int		j;

	printf("%d do_expand(exp_tools)\n", exp_tools->new_len_exp);
	i = -1;
	k = 0;
	new_line = (char *)malloc(exp_tools->new_len_exp * sizeof(char) + 1);
	while (++i < exp_tools->new_len_exp)
	{
		if (j != -1)
			j = -1;
		if (exp_tools->main->first_split[exp_tools->index][k] != '$')
		{
			new_line[i] = exp_tools->main->first_split[exp_tools->index][k];
			printf("1check %c, i%d, k%d\n", new_line[i], i, k);
			k++;
		}
		else if (exp_tools->main->first_split[exp_tools->index][k] == '$')
		{
			j = -1;
			k += (exp_tools->name_len + 1);
			while (++j < ft_strlen(exp_tools->env_ptr->env_cont))
			{
				new_line[i] = exp_tools->env_ptr->env_cont[j];
				printf("2check %c, i%d, k%d\n", new_line[i], i, k);
				i++;
			}
		}
		if (j != -1)
			i--;
	}
	new_line[i] = '\0';
	printf("new_line %s\n", new_line);
}
