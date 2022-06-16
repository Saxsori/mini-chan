/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_envar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 03:42:46 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/15 14:05:38 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

// void	loop_init(t_env_expand *exp_tools, int op)
// {
// 	if (op == 1)
// 	{
// 		if (exp_tools->e != -1)
// 			exp_tools->e = -1;
// 	}
// 	if (op == 2)
// 	{
// 		exp_tools->e = -1;
// 		exp_tools->s += (exp_tools->name_len + 1);
// 	}
// 	if (op == 3)
// 	{
// 		if (exp_tools->e != -1)
// 			exp_tools->i--;
// 	}
// }
// /*
// 	// i = -1;
// 	// while (++i < exp_tools->new_len_exp)
// 	// 	printf("new_line %c, i%d\n", new_line[i], i);
// 	// printf("1check %c, i%d, k%d\n", new_line[i], i, k);
// 	// printf("2check %c, i%d, k%d\n", new_line[i], i, k);
// */	
// void	do_expand(t_env_expand *exp_tools)
// {
// 	char	*new_line;
// 	int		k = 0;
// 	int		j;
// 	// static	int i;
// 	// printf("%d do_expand(exp_tools)\n", exp_tools->new_len_exp);
// 	printf("new len size%d\n", exp_tools->new_len_exp);
// 	printf("%denv index\n", exp_tools->main->env_index[exp_tools->index][exp_tools->env_ord]);
// 	new_line = (char *)malloc(exp_tools->new_len_exp * sizeof(char) + 1);
// 	while (++exp_tools->i < exp_tools->new_len_exp)
// 	{
// 		if (exp_tools->main->env_index[exp_tools->index][exp_tools->env_ord] == k)
// 		{
// 			printf("1->i %d - k %d\n", exp_tools->i, k);
// 			j = -1;
// 			if (exp_tools->env_ptr != NULL)
// 			{	
// 				while (++j < ft_strlen(exp_tools->env_ptr->env_cont))
// 					new_line[exp_tools->i++] = exp_tools->env_ptr->env_cont[j];
// 			}
// 			else
// 				k++;
// 			k += exp_tools->name_len + 1;
// 			exp_tools->i--;
// 			printf("1->i %d - k %d\n", exp_tools->i, k);
// 		}
// 		else
// 		{
// 			// exp_tools->i++;
// 			if (exp_tools->main->first_split[exp_tools->index][k] != '\0')
// 				new_line[exp_tools->i] = exp_tools->main->first_split[exp_tools->index][k];
// 			printf("2->i %d - k %d\n", exp_tools->i, k);
// 			k++;
// 		}
// 	}
// 	new_line[exp_tools->i] = '\0';
// 	printf("%s\n", new_line);
// 	free (exp_tools->main->first_split[exp_tools->index]);
// 	if (new_line[0] != '\0')
// 		exp_tools->main->first_split[exp_tools->index] = ft_strdup(new_line);
// 	else
// 	{
// 		exp_tools->main->first_split[exp_tools->index] = malloc(sizeof(char));
// 		exp_tools->main->first_split[exp_tools->index][0] = '\0';
// 	}
// 	free (new_line);
// 	k = 0;
// 	exp_tools->i = -1;
// 	// int i = -1;
// 	// while (++i < exp_tools->new_len_exp)
// 	// 	printf("n%c\n", exp_tools->main->first_split[exp_tools->index][i]);
// 	printf("new_line %s\n", exp_tools->main->first_split[exp_tools->index]);
// }

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
			exp_tools->s += (exp_tools->env_info[k].name_len - 1);
			
			printf("which env %d, ind-s %d, line-ind%d\n", k, exp_tools->s, exp_tools->i);
			// exp_tools->i += exp_tools->env_info[k].value_len;
			// exp_tools->i--;
			printf("which env %d, ind-s %d, line-ind%d\n", k, exp_tools->s, exp_tools->i);
			k++;
		}
		else
		{
			new_line[exp_tools->i++] = exp_tools->main->first_split[exp_tools->index][exp_tools->s];
			printf("which env %d, ind-s %d, line-ind%d\n", k, exp_tools->s, exp_tools->i);
		}
	}
	new_line[exp_tools->i] = '\0';
	printf ("(%s)\n", new_line);
}