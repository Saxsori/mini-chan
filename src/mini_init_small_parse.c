/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init_small_parse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:11:43 by balnahdi          #+#    #+#             */
/*   Updated: 2022/09/18 13:15:45 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/****************************  PARSE_NULL_ARG  ******************************/
void	init_null_parse(t_null_parse *n_parse)
{
	n_parse->i = -1;
	n_parse->k = -1;
	n_parse->num = 0;
	n_parse->tot_size = 0;
	n_parse->counter = 0;
	n_parse->new_size = 0;
	n_parse->new_line = NULL;
}
/****************************  PARSE_NULL_ARG  *****************************/

/****************************  PARSE_QUOTE  ***********************************/
/*
the beginning of the pars should be the beginning of the command line
-1 b/c it's ++i in loop
the end will be the last index which it should be the length of the 
command line
teh counter of the strings in th quotes should start from when first quotes
encountr so if the first char was quotes the counter should start 
from one instead of 0
*/
/*
? quotes checker
*/
void	init_mini_quotes(t_shell_chan *main, char *line)
{
	main->q_pars.begin = -1;
	main->q_pars.end = ft_strlen(line);
	if (line[0] != 34 && line[0] != 39)
		main->q_pars.q_string = 1;
	else
		main->q_pars.q_string = 0;
	main->q_pars.first = 0;
	main->q_pars.second = 0;
	main->q_pars.exp_index = 0;
}
/****************************  PARSE_QUOTE  ***********************************/
