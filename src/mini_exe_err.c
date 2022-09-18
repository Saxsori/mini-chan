/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exe_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:39:19 by balnahdi          #+#    #+#             */
/*   Updated: 2022/09/18 15:39:29 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	execute_err(t_mini_cmd *cmd)
{
	if ((errno == 2 && cmd->tools.f_path == 1) || \
	(errno == 14 && cmd->tools.y_cmd != 3) || \
	(errno == 2 && cmd->tools.y_cmd == 1))
	{
		if (cmd->tools.y_cmd == 0 && cmd->main->no_path == 0)
			errmsg(cmd->redir.arguments[0], NO_CMD);
		else
			errmsg(cmd->exe_tools.arguments[0], NO_F_DIR);
		ft_exit(cmd->main, 127);
	}
	else if (errno == 13 && cmd->tools.y_cmd == 1)
	{
		errmsg(cmd->exe_tools.arguments[0], PER_ERR);
		ft_exit(cmd->main, 126);
	}
	else
	{
		errmsg(cmd->exe_tools.arguments[0], NO_CMD);
		ft_exit(cmd->main, 127);
	}
}
