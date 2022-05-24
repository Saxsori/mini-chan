/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:12:09 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/24 19:12:38 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	is_there_opt(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	i = -1;
	k = -1;
	while (cmd->split[++i])
	{
		k = -1;
		while (cmd->split[i][++k])
		{
			if (cmd->split[i][k] == '-')
				cmd->tools.opt_num++;
		}
	}
	return (cmd->tools.opt_num);
}

void	get_opt(t_mini_cmd *cmd)
{
	(void) cmd;
	printf("nothing in get_opt\n");
}

/*
check if there is an option 
if yes then try to handle all the cases when u have option 
also if there was no arguments then it's should be the command issue 
so if u have only option execute it like that and check what's the
output
! check this with boo if there is no arguments is there anything to add
! or to fix ..
! check if u should handle the environmental variable if it was an opt
*/
void	check_opt(t_mini_cmd *cmd)
{
	if (is_there_opt(cmd))
		get_opt(cmd);
	else
		cmd->option = NULL;
}
