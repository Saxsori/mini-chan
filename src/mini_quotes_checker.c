/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_quotes_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:23:52 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/15 05:49:09 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
if u find the second quote then change the index to strat from for the 
first loop and return (1) which mean that u find the second one
*/
int	is_closed(t_shell_chan *main, char *line, int index)
{
	while (++index < main->q_pars.end)
	{
		if (line[index] == line[main->q_pars.begin])
		{
			main->q_pars.begin = index;
			return (1);
		}
	}
	return (0);
}

/*
in loop check the quotes if it's closed or not
if ' or " take the index , line to count from there if it will catch
the second quote that will close the forst one if yes 
	then count for hommant strings
if not the return 0 which mean the quote is not closed
*/
int	is_qt_valid(t_shell_chan *main, char *line)
{
	while (++main->q_pars.begin < main->q_pars.end)
	{
		if (line[main->q_pars.begin] == 34 || line[main->q_pars.begin] == 39)
		{
			if (is_closed(main, line, main->q_pars.begin))
				main->q_pars.q_string++;
			else
				return (0);
		}
	}
	return (1);
}

/*
to check if the quotes is closed and valid
? 1- init the structure
? 2- in loop send the strings from the first split
? 3- if it valid the just split and return the value from 
?	the function that will split which is 1
?	else return (0) because the quote is not closed
	! u can here add a function that would point on the that specific 
	!	quote	
			// printf("quotes are valid 1\n");
			printf("quotes are invalid 0\n");
*/
int	quotes_checker(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		init_mini_quotes(main, main->first_split[i]);
		if (is_qt_valid(main, main->first_split[i]))
			main->q_pars.begin = -1;
		else
		{
			errmsg(NULL, "syntax error");
			return (0);
		}
	}
	return (1);
}

/*

	// printf ("old line %s\n", line);
	// while (++n < envar_num(main, i))
	// 	printf ("ind %d, val %d\n", main->env_index[i][n], main->exp_valid[i][n]);

*/
void	tabbing_quote(t_shell_chan *main, char *line, int i)
{
	int	n;

	init_mini_quotes(main, main->first_split[i]);
	find_frst(main, line, i);
	n = -1;
	while (++n < envar_num(main, i))
	{
		if (main->exp_valid[i][n] == -1)
			main->exp_valid[i][n] = 1;
	}
}

void	pre_quote(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
		tabbing_quote(main, main->first_split[i], i);
}
