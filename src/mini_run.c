/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:08:33 by aaljaber          #+#    #+#             */
/*   Updated: 2022/07/26 05:47:34 by dfurneau         ###   ########.fr       */
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
		// i = -1;
		// printf("lo here\n");
		// while (++i < main->cmd_num)
		// {
		// 	if (is_command(main->cmd_table[i].name))
		// 	{
		// 		printf("b %d\n", i);
		// 		printf("b %s\n", main->cmd_table[i].name);
		// 		k = -1;
		// 		while (++k < main->cmd_table[i].tools.arg_num)
		// 			printf("b %s\n", main->cmd_table[i].arguments[k]);
		// 	}
		// 	else if (!is_command(main->cmd_table[i].name))
		// 	{
		// 		printf("e %d\n", i);
		// 		execute_tools(&main->cmd_table[i]);
		// 		k = -1;
		// 		while (++k < main->cmd_table[i].exe_tools.arg_num)
		// 			printf("e %s\n", main->cmd_table[i].exe_tools.arguments[k]);
		// 	}
		// }
	! fix exit status and the error mangement for the execution
	*/
int	run_cmd(t_shell_chan *main)
{
	printf("cmd num %d\n", main->cmd_num);
	get_path(main);
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
			printf("cmd_name %s \n",main->cmd_table[0].exe_tools.cmd_name);
			mini_execute(&main->cmd_table[0]);
			return (1);
		}
	}
	else if (main->cmd_num > 1)
	{
		// main->pipe_tools(main->);
		int	i;
		pipe_tools(main);
		i = -1;
		while (++i < main->cmd_num)
		{
			if (i < main->pipe_tools.p_num)
			{
				if (pipe(main->pipe_tools.fds[i]) < 0)
					perror("pipe add");
			}
			main->pipe_tools.child = fork();
			if (main->pipe_tools.child == 0)
			{
				if (i == 0)
				{
					ft_dup_fds(main, i);
					if (execve(main->cmd_table[i].cmd_path, main->cmd_table[i].exe, NULL) == -1)
					{
						perror("exe");
						exit(127);
					}
				}
				else if ((i == main->pipe_tools.p_num) && ch == 0)
				{
					ft_dup_fds(main, i);
					if (execve(main->cmd_table[i].cmd_path, arg[i], NULL) == -1)
					{
						perror("exe");
						exit(127);
					}
				}
				else
				{
					ft_dup_fds(main, i);
					if (execve(main->cmd_table[i].cmd_path, arg[i], NULL) == -1)
					{
						perror("exe");
						exit(127);
					}
				}
			}
			else
			{
				if (i < main->pipe_tools.p_num)
				{
					if (close(main->pipe_tools.fds[i][1]) == -1)
						perror("first close\n");
				}
				if (i > 0)
				{
					if (close(main->pipe_tools.fds[i - 1][0]) == -1)
						perror("sec close \n");
				}
			}
		}
	}
	return (0);
}
