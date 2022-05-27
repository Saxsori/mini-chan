/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:12:09 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/27 13:08:50 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	find_opt(char *line)
{
	int	i;

	i = -1;
	if (line != NULL)
	{
		while (line[++i])
		{
			if (line[i] == '-')
				return (1);
		}
	}
	return (0);
}

int	is_there_opt(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	i = -1;
	k = -1;
	if (find_opt(cmd->split[1]))
	{
		while (cmd->split[++i])
		{
			k = -1;
			while (cmd->split[i][++k])
			{
				if (cmd->split[i][k] == '-')
					cmd->tools.opt_num++;
			}
		}
	}
	return (cmd->tools.opt_num);
}

void	pre_opt(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	cmd->option = (char **)malloc(cmd->tools.opt_num * sizeof(char *));
	while (++i < cmd->tools.opt_num)
		cmd->option[i] = (char *)malloc(ft_strlen(cmd->split[++k]));
}

void	get_opt(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	pre_opt(cmd);
	i = -1;
	k = 0;
	while (++i < cmd->tools.opt_num)
		cmd->option[i] = cmd->split[++k];
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
