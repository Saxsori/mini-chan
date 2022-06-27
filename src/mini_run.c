/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:24:05 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/27 20:11:54 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
	// i = -1;
	// while (++i < main->cmd_num)
	// {
	// 	if (!is_command(main->cmd_table[i].name))
	// 	{
	// 		execute_tools(&main->cmd_table[i]);
	// 		main->cmd_table[i].y_exe = 1;
	// 	}
	// 	else if (is_command(main->cmd_table[i].name))
	// 	{
	// 		main->cmd_table[i].y_exe = 0;
			
	// 	}
	// }
	*/
int	run_cmd(t_shell_chan *main)
{
	if (main->cmd_num == 1)
	{
		init_mini_cmd(&main->cmd_table[0], main);
		check_opt(&main->cmd_table[0]);
		check_arg(&main->cmd_table[0]);
		if (is_command(main->cmd_table[0].name))
		{
			return (run_builtn(&main->cmd_table[0]));
		}
		else if (!is_command(main->cmd_table[0].name))
		{
			execute_tools(&main->cmd_table[0]);
			mini_execute(&main->cmd_table[0]);
			return (0);
		}
	}
	return (0);
}
