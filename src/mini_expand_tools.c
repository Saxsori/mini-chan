/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:05:41 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/15 00:49:50 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	check_ignore_case(t_shell_chan *main, int i, int k, int num)
{
	char	q;

	if (k == 0)
		num--;
	else
	{
		q = main->first_split[i][k + 1];
		if (main->first_split[i][k - 1] != q)
			num--;
	}
	return (num);
}

/*
? $$ case
this was after j++
			// if (main->first_split[i][k + 1] == '$')
			// 	k += 1;
			// if (main->first_split[i][k + 1] == 34 || main->first_split[i][k + 1] == 39 
			// || main->first_split[i][k + 1] == '\t')
			// 	j = check_ignore_case(main, i, k, j);
*/
int	envar_num(t_shell_chan *main, int i)
{
	int		k;
	int		j;

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
? $$ case
this was after j++
			// if (main->first_split[i][k + 1] == '$')
			// 	k += 1;
 
*/
void	find_env_index(t_shell_chan *main, int i)
{
	int	k;
	int	j;

	k = -1;
	j = 0;
	while (++k < ft_strlen(main->first_split[i]) && j <= envar_num(main, i))
	{
		if (main->first_split[i][k] == '$')
		{
			main->env_index[i][j] = k;
			j++;
			if (main->first_split[i][k + 1] == 34 || \
			main->first_split[i][k + 1] == 39)
				j = check_ignore_case(main, i, k, j);
		}
	}
}

void	two_dollar_case(char *line)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '$')
		{
			if (line[i + 1] == '$')
			{
				line[i] = '\t';
				line[i + 1] = '\t';
			}
		}
	}
}

/*

	// i = -1;
	// while (++i < main->cmd_num)
	// {
	// 	k = -1;
	// 	while (++k < envar_num(main, i))
	// 		printf ("ind - %d\n", main->env_index[i][k]);
	// }
	// printf ("line %s\n", main->first_split[0]);
	// printf ("envar num %d\n", envar_num(main, 0));
? $$ case
this was on the line 108
	// i = -1;
	// while (++i < main->cmd_num)
	// 	two_dollar_case(main->first_split[i]);
		printf("envar num %d in index %d line %s\n",
		 envar_num(main, i), i, main->first_split[i]);
*/
void	expand_tools(t_shell_chan *main)
{
	int	i;
	int	k;

	main->exp_valid = (int **)malloc(main->cmd_num * sizeof(int *));
	main->env_index = (int **)malloc(main->cmd_num * sizeof(int *));
	i = -1;
	while (++i < main->cmd_num)
	{
		main->exp_valid[i] = (int *)malloc(envar_num(main, i) * sizeof(int));
		main->env_index[i] = (int *)malloc(envar_num(main, i) * sizeof(int));
	}
	i = -1;
	while (++i < main->cmd_num)
	{
		k = -1;
		while (++k < envar_num(main, i))
			main->exp_valid[i][k] = -1;
		find_env_index(main, i);
	}
}
