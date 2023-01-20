/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_run_one_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:54:42 by balnahdi          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

void	run_one_redir(t_shell_chan *main)
{
	if (!check_redir_flag(main->cmd_table))
		redir(&main->cmd_table[0]);
	else
	{
		if (!check_redir_heredoc(main->cmd_table))
		{
			if (main->path)
				redir_heredoc(&main->cmd_table[0]);
			else
			{
				errmsg(main->cmd_table[0].name, NO_F_DIR);
				g_status = 127;
			}
		}
		else
			printf("SYNTAX ERROR\n");
	}
}
