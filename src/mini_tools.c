/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:48:11 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 14:36:16 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	do_pipe_split(t_shell_chan *main)
{
	if (main->cmd_num > 1)
	{
		main->first_split = ft_split(main->cmd_line, '|');
		if (!main->first_split)
		{
			main->exit_status = 2;
			if (ft_strlen(main->cmd_line) == 1)
				printf (BRED"mini-chan🌸: syntax error near unexpected token `|'\n");
			else if (ft_strlen(main->cmd_line) > 1)
				printf (BRED"mini-chan🌸: syntax error near unexpected token `||'\n");
		}
		else if (!check_pipe(main->cmd_line))
		{
			main->exit_status = 2;
			printf (BRED"mini-chan🌸: syntax error near unexpected token `|'\n");
		}
	}
	else
	{
		main->first_split = (char **)malloc(sizeof (char *) * 2);
		main->first_split[0] = ft_strdup(main->cmd_line);
		main->first_split[1] = NULL;
	}
}

/*
? 1- counting how many commands are there
? 2- depending on that counter do the malloc for the array of structures
? 3- if it was more than 1 then split them
?		else just take that one command and save it on first split
? 4- call function split command to split the parts and 
?	save each command on it's own structure

	BOO
todo	check || in mid of cmd line AND |     |  AND cmd|cmd||||cmd
		handel DONE ( cmd | cmd ||)
*/
void	first_cmd_split(t_shell_chan *main)
{
	check_valid_pipe(main);
	cmd_counter(main);
	main->cmd_table = (t_mini_cmd *)malloc(main->cmd_num * sizeof(t_mini_cmd));
	init_mini_cmd_loop(main);
	do_pipe_split(main);
	if (main->exit_status != 2)
		return_invalid_pipe(main);
}
