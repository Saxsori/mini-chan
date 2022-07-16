/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:08:33 by aaljaber          #+#    #+#             */
/*   Updated: 2022/07/16 07:12:17 by aaljaber         ###   ########.fr       */
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
	! fix exit status and the error mangement for the execution
	*/
int	run_cmd(t_shell_chan *main)
{
	int	i;
	int	k;

	printf("cmd num %d\n", main->cmd_num);
	if (main->cmd_num == 1)
	{
		if (is_command(main->cmd_table[0].name))
		{
			printf("isredir %d\n", main->cmd_table[0].tools.y_redir);
			return (run_builtn(&main->cmd_table[0]));
		}
		else if (!is_command(main->cmd_table[0].name))
		{
			execute_tools(&main->cmd_table[0]);
			mini_execute(&main->cmd_table[0]);
			return (1);
		}
	}
	else if (main->cmd_num > 1)
	{
		i = -1;
		printf("lo here\n");
		while (++i < main->cmd_num)
		{
			if (is_command(main->cmd_table[i].name))
			{
				printf("b %d\n", i);
				printf("b %s\n", main->cmd_table[i].name);
				k = -1;
				while (++k < main->cmd_table[i].tools.arg_num)
					printf("b %s\n", main->cmd_table[i].arguments[k]);
			}
			else if (!is_command(main->cmd_table[i].name))
			{
				printf("e %d\n", i);
				execute_tools(&main->cmd_table[i]);
				k = -1;
				while (++k < main->cmd_table[i].exe_tools.arg_num)
					printf("e %s\n", main->cmd_table[i].exe_tools.arguments[k]);
			}
		}	
	}
	return (0);
}
