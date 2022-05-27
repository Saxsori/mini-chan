/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:17:28 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/26 20:12:38 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
? 1- save each command name in it's structure member
? 2- check if that command name is valid then return one 
?		to check then the other command parts
!! CHECK THIS WITH BOO if this needs edition 
!  depending on the other 
!  builtin commands since this will only work with the commands that
!  abrar did
	// while (++i < main->cmd_num)
	// 	printf("%s\n", main->cmd_table[i].name);
*/
int	command_name(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
		main->cmd_table[i].name = main->cmd_table[i].split[0];
	i = -1;
	while (++i < main->cmd_num)
	{
		if (!is_command(main->cmd_table[i].name))
		{
			printf(BRED"mini-chan🌸: %s: command not found\n" \
				, main->cmd_table[i].name);
			return (0);
		}
	}
	return (1);
}
