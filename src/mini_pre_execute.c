/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pre_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:37:27 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/27 20:54:33 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"
	/*
	// i = -1;
	// while (++i < cmd->exe_tools.arg_num)
	// 	printf("arg %s\n", cmd->exe_tools.arguments[i]);
	// printf ("cmd %s\n", cmd->exe_tools.cmd_name);
	*/
void	execute_tools(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	cmd->exe_tools.cmd_name = ft_strdup(cmd->name);
	free (cmd->name);
	cmd->exe_tools.arg_num = cmd->tools.arg_num + cmd->tools.opt_num + 1;
	printf("num %d\n", cmd->exe_tools.arg_num);
	cmd->exe_tools.arguments = (char **)malloc(sizeof(char *) * (cmd->exe_tools.arg_num + 1));
	cmd->exe_tools.arguments[0] = ft_strdup(cmd->exe_tools.cmd_name);
	i = 0;
	printf("op num %d\n", cmd->tools.opt_num);
	printf("arg num %d\n", cmd->tools.arg_num);
	if (cmd->tools.opt_num > 0)
	{	
		k = -1;
		i = 0;
		while (++k < cmd->tools.opt_num)
		{
			cmd->exe_tools.arguments[++i] = ft_strdup(cmd->option[k]);
		}
	}
	if (cmd->tools.arg_num > 0)
	{
		k = -1;
		while (++k < cmd->tools.arg_num)
		{
			cmd->exe_tools.arguments[i++] = ft_strdup(cmd->arguments[k]);
		}
	}
	cmd->exe_tools.arguments[cmd->exe_tools.arg_num + 1] = NULL;
}
