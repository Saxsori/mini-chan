/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:50:49 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/31 17:34:40 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	init_shell_chan(t_shell_chan *main)
{
	main->cmd_line = NULL;
	main->cmd_num = 0;
	main->exit_status = EXIT_SUCCESS;
	main->d_rootpath = 0;
}

void	re_init_shell_chan(t_shell_chan *main)
{
	main->cmd_num = 0;
}

void	init_mini_cmd(t_mini_cmd *cmd, t_shell_chan *main)
{
	cmd->arguments = NULL;
	cmd->option = NULL;
	cmd->main = main;
	cmd->tools.arg_num = 0;
	cmd->tools.opt_num = 0;
	cmd->tools.arg_index = 0;
	cmd->tools.y_op = 0;
	cmd->tools.y_arg = 0;
	cmd->tools.p_num = 0;
}

/*
the beginning of the pars should be the beginning of the command line
-1 b/c it's ++i in loop
the end will be the last index which it should be the length of the 
command line
teh counter of the strings in th quotes should start from when first quotes
encountr so if the first char was quotes the counter should start 
from one instead of 0
*/
// void	init_mini_quotes(t_mini_cmd *cmd)
// {
// 	cmd->tools.q_pars->begin = -1;
// 	cmd->tools.q_pars->end = ft_strlen(cmd->main->cmd_line);
// 	if (cmd->main->cmd_line[0] != 34 && cmd->main->cmd_line[0] != 39)
// 		cmd->tools.q_pars->q_string = 1;
// 	else
// 		cmd->tools.q_pars->q_string = 0;
// }
