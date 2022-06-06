/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_quotes_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:23:52 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/06 00:01:14 by aaljaber         ###   ########.fr       */
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
*/
int	quotes_checker(t_shell_chan *main)
{
	int	i;
	int	k;

	i = -1;
	while (++i < main->cmd_num)
	{
		init_mini_quotes(main, main->first_split[i]);
		if (is_qt_valid(main, main->first_split[i]))
		{
			printf("quotes are valid 1\n");
			main->q_pars.begin = -1;
			if (!quote_split(main, main->first_split[i], i))
				return (0);
		}
		else
		{
			printf("quotes are invalid 0\n");
			return (0);
		}	
	}
	i = -1;
	while (++i < main->cmd_num)
	{
		k = -1;
		while (++k < envar_num(main, i))
			printf ("v%d -> %d\ni%d -> %d\n", i, main->exp_valid[i][k], i, main->env_index[i][k]);
	}
	return (1);
}
