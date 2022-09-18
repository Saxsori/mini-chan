/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:08:03 by balnahdi          #+#    #+#             */
/*   Updated: 2022/09/18 13:40:22 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/****************************  CMD_TABLE  ***********************************/
void	init_cmd_tools(t_mini_cmd *cmd)
{
	cmd->tools.y_cmd = -1;
	cmd->tools.arg_num = 0;
	cmd->tools.opt_num = 0;
	cmd->tools.arg_index = 0;
	cmd->tools.y_op = 0;
	cmd->tools.y_arg = 0;
	cmd->tools.i_arg = 0;
	cmd->tools.p_num = 0;
	cmd->tools.f_redir = 0;
	cmd->tools.y_redir = 0;
	cmd->tools.y_exe = 0;
	cmd->tools.new_arg = 0;
	cmd->tools.new_arg_size = 0;
	cmd->tools.r_err_syn = 0;
	cmd->tools.cwd_ret = NULL;
	cmd->tools.dir = NULL;
	cmd->tools.envar = NULL;
	cmd->tools.pwd = NULL;
	init_predir(&cmd->tools.p_redir);
}

void	init_mini_cmd(t_mini_cmd *cmd, t_shell_chan *main)
{
	cmd->main = main;
	cmd->name = NULL;
	cmd->split = NULL;
	cmd->option = NULL;
	cmd->arguments = NULL;
	cmd->cmd_path = NULL;
	cmd->status = 0;
	cmd->null_cmd_line = 0;
	init_cmd_tools(cmd);
	init_first_redir(cmd);
	cmd->exe_tools.arg_num = 0;
	cmd->exe_tools.arguments = NULL;
	cmd->exe_tools.cmd_name = NULL;
	cmd->exe_tools.err_command = NULL;
}

void	init_mini_cmd_loop(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
		init_mini_cmd(&main->cmd_table[i], main);
}
/****************************  CMD_TABLE  ***********************************/

void	init_first_redir(t_mini_cmd *cmd)
{
	cmd->redir.arguments = NULL;
	cmd->redir.command = NULL;
	cmd->redir.files = NULL;
	cmd->redir.redir = NULL;
	cmd->redir.redir_tools.i = 0;
	cmd->redir.redir_tools.j = 0;
	cmd->redir.redir_tools.k = 0;
	cmd->redir.redir_tools.main = NULL;
	cmd->redir.redir_tools.num_arg = 0;
	cmd->redir.redir_tools.num_file = 0;
	cmd->redir.redir_tools.num_part = 0;
	cmd->redir.redir_tools.num_redir = 0;
	cmd->redir.redir_tools.parse_err = 0;
	cmd->redir.redir_tools.r_pos = NULL;
	cmd->redir.redir_tools.split = NULL;
	cmd->redir.redir_tools.fd = NULL;
}
