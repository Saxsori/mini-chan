/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_pre.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:10:24 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/18 10:37:02 by aaljaber         ###   ########.fr       */
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

int	env_pos(t_shell_chan *main, int i, int index)
{
	int	k;

	k = -1;
	while (++k < envar_num(main, i))
	{
		if (main->env_index[i][k] == index)
			return (k);
	}
	return (-1);
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
	// printf("b4 replacing tab %d\n", envar_num(main, 0));
	// while (++i < main->cmd_num)
	// {
	// 	n = -1;
	// 	while (++n < ft_strlen(main->first_split[i]))
	// 	{
	// 		// printf("n -> %d\n", n);
	// 		if (main->first_split[i][n] == '$')
	// 		{
	// 			if (main->first_split[i][n + 1] == '$')
	// 			{
	// 				if (main->first_split[i][env_pos(main, i, n + 1) != 2])
	// 					main->first_split[i][n + 1] = '\t';
	// 			}
	// 		}	
	// 	}
	// }
	printf("line after q_split -> (%s) \n", main->first_split[0]);
	i = -1;
	while (++i < main->cmd_num)
	{
		n = -1;
		while (++n < envar_num(main, i))
			printf("ind->%d valid->%d \n", main->env_index[i][n], main->exp_valid[i][n]);
	}
}

int	get_envar_ending(char *line, int start)
{
	int	i;

	i = start;
	while (++i <= ft_strlen(line))
	{
		// printf("i - %d\n", i);
		if (line[i] == '\t')
			return (i);
		if (line[i] == ' ')
			return (i);
		else if (line[i] == '\0')
			return (i);
		else if (line[i] == 34)
			return (i);
		else if (line[i] == 39)
			return (i);
		else if (line[i] == '\v')
			return (i);
		else if (line[i] == '$')
		{
			if (line[i - 1] == '$')
				return (i + 1);
			else 
				return (i);
		}
	}
	printf("here\n");
	return (0);
}

int	get_envar_len(char *line, int index)
{
	// printf ("ending - %d || start - %d\n", get_envar_ending(line, index), index);
	return (get_envar_ending(line, index) - (index + 1));
}

int	envar_n_ending_with_quote(char *line, int i)
{
	if (line[i - 1] != 34 && line[i - 1] != 39)
	{
		if (line[i + 1] != 34 && line[i + 1] != 39)
		{
			if (line[i + 1] != '$' && line[i - 1] != '$')
			{
				if (line[i + 1] != '\t' && line[i - 1] != '\t')
					return (1);
			}
		}
	}
	return (0);
}

int	get_len_b4_quote(char *line, int i)
{
	int	j;

	j = 0;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '\t')
			return (j);
		j++;
	}
	return (0);
}

int	envar_surr_by_quote(char *line, int i)
{
	int	j;

	printf ("i %d line[i - 1] '%c'\n", i, line[i - 1]);
	if (line[i - 1] == '\t')
	{
		j = i;
		while (++j < ft_strlen(line))
		{
			if (line[j] == '\t')
			{
				if (j + 1 < ft_strlen(line))
				{
					if (line [j + 1] != ' ' || line [j + 1] != '\v')
						return (1);
				}
			}
		}
	}
	return (0);
}

void	find_env_length(t_shell_chan *main, char *line, int i)
{
	int	k;
	int	j;

	k = -1;
	j = 0;
	printf("envar num - %d\n", envar_num(main, i));
	printf("this line - %s\n", line);
	while (++k < ft_strlen(line) && j < envar_num(main, i))
	{
		// printf ("k - %d\n", k);
		if (k == main->env_index[i][j])
		{
			printf ("index - %d\n", k);
			if (envar_n_ending_with_quote(line, k))
			{
				main->env_n_len[i][j] = get_envar_len(line, k);
				printf("1 hheeelloo\n");
			}
			else if (envar_surr_by_quote(line, k))
			{
				main->env_n_len[i][j] = get_len_b4_quote(line, k);
				printf("2 hheeelloo\n");
			}
			else
			{
				printf("1 here\n");
				main->env_n_len[i][j] = 0;
			}
			printf ("length - %d\n", main->env_n_len[i][j]);
			j++;
		}
	}
}
