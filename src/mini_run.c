/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:22:19 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/15 09:49:15 by aaljaber         ###   ########.fr       */
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
int	check_redir_heredoc(t_mini_cmd *cmd)
{
	int	i;

	i = 0;
	while ((i < cmd->redir.redir_tools.num_redir) && \
	(!ft_strncmp(cmd->redir.redir[i], "<<", ft_strlen(">>"))))
		i++;
	if (i == cmd->redir.redir_tools.num_redir)
		return (0);
	return (1);
}

int	check_redir_flag(t_mini_cmd *cmd)
{
	int	i;

	i = 0;
	while ((i < cmd->redir.redir_tools.num_redir) && \
	(!ft_strncmp(cmd->redir.redir[i], ">", ft_strlen(">")) || \
	!ft_strncmp(cmd->redir.redir[i], ">>", ft_strlen(">>")) || \
	!ft_strncmp(cmd->redir.redir[i], "<", ft_strlen("<"))))
		i++;
	if (i == cmd->redir.redir_tools.num_redir)
		return (0);
	else
		return (1);
	return (1);
}

int	run_cmd(t_shell_chan *main)
{
	// int	i;

	// i = 0;
	get_path(main);
	if (main->cmd_num == 1)
	{
		if (main->cmd_table->tools.y_redir)
		{
			if (!main->cmd_table->redir.files)
				printf("yes\n");
			if (!check_redir_flag(main->cmd_table))
			{
				// printf("check redir %d \n", check_redir_flag(main->cmd_table));
				redir(&main->cmd_table[0]);
			}
			else
			{
				if (!check_redir_heredoc(main->cmd_table))
				{
					// printf("check redir heredoc  %d \n", check_redir_flag(main->cmd_table));
					redir_heredoc(&main->cmd_table[0]);
				}
				else
					printf("SYNTAX ERROR\n");
			}
		}
		else if (is_command(main->cmd_table[0].name))
		{
			// printf("isredir %d\n", main->cmd_table[0].tools.y_redir);
			g_status = run_builtn(&main->cmd_table[0]);
			return (g_status);
		}
		else if (!is_command(main->cmd_table[0].name))
		{
			// TODO : if (!main->path)
			if (main->path)
			{
				execute_tools(&main->cmd_table[0]);
				mini_execute(&main->cmd_table[0]);
			}
			else
			{
				printf("mini-chan🌸: %s: No such file or directory\n", \
				main->cmd_table[0].name);
				g_status = 127;
			}
			return (g_status);
		}
	}
	if (main->cmd_num > 1)
	{
		pipe_tools(main);
		ft_mini_pipe(main);
	}
	return (0);
}
