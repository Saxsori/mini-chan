/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:48:11 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/23 19:49:30 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	cmd_counter(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(main->cmd_line))
	{
		if (main->cmd_line[i] == '|')
			main->cmd_num++;
	}
	main->cmd_num++;
}

/*
? 1- counting how many commands are there
? 2- depending on that counter do the malloc for the array of structures
? 3- if it was more than 1 then split them
?		else just take that one command and save it on first split
? 4- call function split command to split the parts and 
?	save each command on it's own structure
*/
void	mini_tools(t_shell_chan *main)
{
	cmd_counter(main);
	main->cmd_table = (t_mini_cmd *)malloc(main->cmd_num * sizeof(t_mini_cmd));
	if (main->cmd_num > 1)
		main->first_split = ft_split(main->cmd_line, '|');
	else
		main->first_split = &main->cmd_line;
	split_command(main);
}
