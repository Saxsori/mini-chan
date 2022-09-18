/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:48:11 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/18 11:49:07 by aaljaber         ###   ########.fr       */
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
				printf (BRED PIPE_ERR1);
			else if (ft_strlen(main->cmd_line) > 1)
				printf (BRED PIPE_ERR2);
		}
		else if (!check_pipe(main->cmd_line))
		{
			main->exit_status = 2;
			printf (BRED PIPE_ERR1);
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

/*
	// i = 0;
	// while (i < cmd->exe_tools.arg_num)
	// 	printf("arg '%s'\n", cmd->exe_tools.arguments[i++]);


	todo 
		126 exit code use access(x_ok)
	todo
		/bin/lss not found should know the errno
*/

void	msg(int i)
{
	if (i == SIGQUIT)
		printf("Quit\n");
}
