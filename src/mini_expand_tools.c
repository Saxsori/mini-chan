/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:10:24 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/04 13:36:18 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	envar_num(t_shell_chan *main, int i)
{
	int	k;
	int	j;

	k = -1;
	j = 0;
	while (++k < ft_strlen(main->first_split[i]))
	{
		if (main->first_split[i][k] == '$')
			j++;
	}
	return (j);
}

/*
here to create 2d array each array for each command 
and each element for each envar in one command line
? this has been created to decide by then if this envar should be 
? expanded or not -1 means nothing decided 0 means it shouldn't 1 means it should
	// i = -1;
	// while (++i < main->cmd_num)
	// 	printf("env num%d\n", envar_num(main, i));
	// i = -1;
	// while (++i < main->cmd_num)
	// {
	// 	k = -1;
	// 	while (++k < envar_num(main, i))
	// 		printf ("%d -> %d\n", i, main->exp_valid[i][k]);
	// }
*/
void	expand_tools(t_shell_chan *main)
{
	int	i;
	int	k;

	main->exp_valid = (int **)malloc(main->cmd_num * sizeof(int *));
	i = -1;
	while (++i < main->cmd_num)
		main->exp_valid[i] = (int *)malloc(envar_num(main, i) * sizeof(int));
	i = -1;
	while (++i < main->cmd_num)
	{
		k = -1;
		while (++k < envar_num(main, i))
			main->exp_valid[i][k] = -1;
	}
}
