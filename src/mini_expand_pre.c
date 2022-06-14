/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_pre.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:10:24 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/14 12:11:19 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"
/*
* BEFORE THE QUOTES PASER TO PREPARE THE EXPANDING THING
* AND WHILE THE QUOTES PARSING CHECK THE VALIDITY OF EACH ENV AND IT'S INDEX
*/
/*
returns how many env var are there
*/
int	envar_num(t_shell_chan *main, int i)
{
	int	k;
	int	j;

	k = -1;
	j = 0;
	while (++k < ft_strlen(main->first_split[i]))
	{
		if (main->first_split[i][k] == '$')
		{
			if (main->first_split[i][k + 1] == '$')
				k += 1;
			j++;
		}
	}
	return (j);
}

/*
to find in which index is the env
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
			if (main->first_split[i][k + 1] == '$')
				k += 1;
		}
	}
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
	main->env_index = (int **)malloc(main->cmd_num * sizeof(int *));
	main->env_n_len = (int **)malloc(main->cmd_num * sizeof(int *));
	i = -1;
	while (++i < main->cmd_num)
	{
		main->exp_valid[i] = (int *)malloc(envar_num(main, i) * sizeof(int));
		main->env_index[i] = (int *)malloc(envar_num(main, i) * sizeof(int));
		main->env_n_len[i] = (int *)malloc(envar_num(main, i) * sizeof(int));
	}
	i = -1;
	while (++i < main->cmd_num)
	{
		k = -1;
		while (++k < envar_num(main, i))
		{
			main->exp_valid[i][k] = -1;
			main->env_n_len[i][k] = -1;
		}
		find_env_index(main, i);
	}
	// printf ("%d\n", envar_num(main, 0));
	// i = -1;
	// while (++i < main->cmd_num)
	// {
	// 	k = -1;
	// 	while (++k < envar_num(main, i))
	// 		printf ("i - %d\n", main->env_index[i][k]);
	// }
}

/*
? 1- everything doesn't have a validity yet means it's just a normal case
? so it's all should be one
? 2- if thers is two $ means it's the builtin var in bash which it should
? expand to the PID so to make it easy in parsing I will replace it to \t
? so that $\t means PID and the other $ with nothing should stay $ and 
? the other $ with anything should expand to nothing
*/
void	expand_pre(t_shell_chan *main)
{
	int	i;
	int	n;

	i = -1;
	while (++i < main->cmd_num)
	{
		n = -1;
		while (++n < envar_num(main, i))
		{
			if (main->exp_valid[i][n] == -1)
				main->exp_valid[i][n] = 1;
		}
		find_env_index(main, i);
	}
	i = -1;
	while (++i < main->cmd_num)
	{
		n = -1;
		while (++n < ft_strlen(main->first_split[i]))
		{
			// printf("n -> %d\n", n);
			if (main->first_split[i][n] == '$')
			{
				if (main->first_split[i][n + 1] == '$')
					main->first_split[i][n + 1] = '\t';
			}	
		}
	}
	printf("line after q_split -> (%s) \n", main->first_split[0]);
	i = -1;
	while (++i < main->cmd_num)
	{
		n = -1;
		while (++n < envar_num(main, i))
			printf("ind->%d valid->%d \n", main->env_index[i][n], main->exp_valid[i][n]);
	}
}

void	find_env_length(t_shell_chan *main, char *line, int i)
{
	
}