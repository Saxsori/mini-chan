/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pre_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:37:27 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/28 17:59:54 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	init_mini_exe_tools(t_mini_cmd *cmd)
{
	cmd->exe_tools.cmd_name = ft_strdup(cmd->name);
	cmd->exe_tools.arg_num = cmd->tools.arg_num + cmd->tools.opt_num + 1;
	cmd->exe_tools.arguments = (char **)malloc(sizeof(char *) \
	* (cmd->exe_tools.arg_num + 1));
	cmd->exe_tools.arguments[0] = ft_strdup(cmd->exe_tools.cmd_name);
	cmd->exe_tools.envar = search_envar(cmd->main->head_envar, "PATH");
	cmd->exe_tools.path = ft_strdup(cmd->exe_tools.envar->env_cont);
	cmd->exe_tools.path_split = ft_split(cmd->exe_tools.path, ':');
	cmd->exe_tools.err_command = ft_strdup(cmd->exe_tools.cmd_name);
}

void	get_arguments(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	if (cmd->tools.opt_num > 0)
	{	
		k = -1;
		i = 1;
		while (++k < cmd->tools.opt_num)
			cmd->exe_tools.arguments[i++] = ft_strdup(cmd->option[k]);
	}
	if (cmd->tools.arg_num > 0)
	{
		k = -1;
		if (cmd->tools.opt_num <= 0)
			i = 1;
		while (++k < cmd->tools.arg_num)
			cmd->exe_tools.arguments[i++] = ft_strdup(cmd->arguments[k]);
	}
	cmd->exe_tools.arguments[cmd->exe_tools.arg_num] = NULL;
}

/*
	// i = -1;
	// while (++i < cmd->exe_tools.arg_num)
	// 	printf("arg %s\n", cmd->exe_tools.arguments[i]);
	// printf ("cmd %s\n", cmd->exe_tools.cmd_name);
	// i = -1;
	// while (++i < cmd->exe_tools.arg_num + 1)
	// 	printf ("%d -> %s\n", i, cmd->exe_tools.arguments[i]);
*/
void	execute_tools(t_mini_cmd *cmd)
{
	init_mini_exe_tools(cmd);
	get_arguments(cmd);
}
