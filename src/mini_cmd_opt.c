/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:12:09 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/25 20:18:58 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
	// if (line != NULL)
	// {
		// while (line[++i])
		// {
			if (line[i] == '-')
				return (1);
	// 	}
	// }
*/
int	find_opt(char *line)
{
	if (line != NULL)
	{
		if (line[0] == '-')
			return (1);
	}
	return (0);
}

int	is_there_opt(t_mini_cmd *cmd)
{
	int	i;

	i = 0;
	if (find_opt(cmd->split[1]))
	{
		while (cmd->split[++i])
		{
			if (cmd->split[i][0] == '-')
				cmd->tools.opt_num++;
			else
				return (cmd->tools.opt_num);
		}
	}
	return (cmd->tools.opt_num);
}

void	pre_opt(t_mini_cmd *cmd)
{
	cmd->option = (char **)malloc((cmd->tools.opt_num + 1) * sizeof(char *));
	cmd->option[cmd->tools.opt_num] = NULL;
}

void	get_opt(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	pre_opt(cmd);
	i = -1;
	k = 0;
	while (++i < cmd->tools.opt_num)
		cmd->option[i] = ft_strdup(cmd->split[++k]);
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
	{
		get_opt(cmd);
	}
	else
		cmd->option = NULL;
}
