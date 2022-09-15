/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_isvalid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:17:43 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 07:49:48 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
? in the array of validity of redir i will mark that redir as invalid redir
? and i will return back the new index to continue after the closing quote 
			// printf ("inside %d\n", begin);
			// printf("redir pos %d\n", redir_pos(cmd, begin));
*/
void	is_btwn_quote(t_mini_cmd *cmd, char *line, int begin)
{
	while (++begin < cmd->tools.p_redir.end)
	{
		if ((line[begin] == '>' || line[begin] == '<') && \
		redir_pos(cmd, begin) != -1)
			cmd->tools.p_redir.r_valid[redir_pos(cmd, begin)] = 0;
		if (line[begin] == line[cmd->tools.p_redir.begin])
		{
			cmd->tools.p_redir.begin = begin;
			return ;
		}
	}
}

/*
to check if the redir is not btwn quote ">>"
? ->>> the line is in loop
? 1- if there is quote " or '
? 2- take the index and the line to check btwn the quote is there ant redir
*/
void	not_btwn_quote(t_mini_cmd *cmd, char *line)
{
	while (++cmd->tools.p_redir.begin < cmd->tools.p_redir.end)
	{
		if (line[cmd->tools.p_redir.begin] == 34 || \
		line[cmd->tools.p_redir.begin] == 39)
			is_btwn_quote(cmd, line, cmd->tools.p_redir.begin);
	}
}

/*

to check if there ie no more than two redir >>>
?  if it was redir
	-> check it's index 
		-> if it was not already marked as 0 (cuz it means it's btwn quote)
			-> get the last index that has the redir 
			-> if first index and the last index minus each other equal to 2
			-> means it's more than two so it's a syntax error
			-> fill the validity array for that pecific redir as a syntax error
					// printf ("k - i = %d\n", k - i);
*/
void	not_more_than_two(t_mini_cmd *cmd, char *line)
{
	int	i;
	int	k;

	i = -1;
	k = i;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (is_redir_index(cmd, i))
			{
				if (cmd->tools.p_redir.r_valid[redir_pos(cmd, i)] != 0)
				{
					k = last_redir(line, i);
					if (k - i > 2)
						cmd->tools.p_redir.r_valid[redir_pos(cmd, i)] = 2;
				}
			}
		}
	}
}

/*
? starting from that  redir
? if it was > then the second shouldn't be <
? if it was < then the second shouldn't be >
*/
int	is_opp_redir(char *line, int index)
{
	index--;
	while (++index < ft_strlen(line))
	{
		if (line[index] == '>')
		{
			if (line[index + 1] == '<')
				return (1);
		}
		else if (line[index] == '<')
		{
			if (line[index + 1] == '>')
				return (1);
		}
	}
	return (0);
}

/*
? if redir
? 	-> if it was one of the redir index 
? 		(cuz it may be the second redir from the multiple redir)
? 		-> if it was a valid redir
? 			-> check if there was an opp redir -- take the index
? 				-> **yes -> then mark this as syntax error**
*/
void	not_opp_redir(t_mini_cmd *cmd, char *line)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (is_redir_index(cmd, i))
			{
				if (cmd->tools.p_redir.r_valid[redir_pos(cmd, i)] != 0)
				{
					if (is_opp_redir(line, i))
					{
						cmd->tools.p_redir.r_valid[redir_pos(cmd, i)] = 2;
					}
				}
			}
		}
	}
}
