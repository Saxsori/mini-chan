/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:08:33 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/29 18:59:07 by aaljaber         ###   ########.fr       */
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
	printf("lala\n");
	if (main->cmd_num == 1)
	{
		// if (main->cmd_table->tools.y_redir)
		// {
		// 	printf("------ heredoc");
		// 	if (!check_redir_flag(main->cmd_table))
		// 	{
		// 		printf("check redir %d \n", check_redir_flag(main->cmd_table));
		// 		// redir(&main->cmd_table[0]);
		// 	}
		// 	else
		// 	{
		// 		if (!check_redir_heredoc(main->cmd_table))
		// 		{
		// 			printf("check redir heredoc  %d \n", check_redir_flag(main->cmd_table));
		// 			redir_heredoc(&main->cmd_table[0]);
		// 		}
		// 		else
		// 			printf("SYNTAX ERROR\n");
		// 	}
		// }
		/*else*/ if (is_command(main->cmd_table[0].name))
		{
			// printf("isredir %d\n", main->cmd_table[0].tools.y_redir);
			return (run_builtn(&main->cmd_table[0]));
		}
		else if (!is_command(main->cmd_table[0].name))
		{
			// TODO : if (!main->path)
			execute_tools(&main->cmd_table[0]);
			// printf("2 cmd_name %s \n", main->cmd_table[0].exe_tools.cmd_name);
			mini_execute(&main->cmd_table[0]);
			printf("vooooooo\n");
			return (1);
		}
	}
	// if (main->cmd_num > 1)
	// {
	// 	pipe_tools(main);
	// 	i = -1;
	// 	while (++i < main->cmd_num)
	// 	{
	// 		if (i < main->pipe_tools.p_num)
	// 		{
	// 			if (pipe(main->pipe_tools.fds[i]) < 0)
	// 				perror("pipe add");
	// 		}
	// 		main->pipe_tools.child = fork();
	// 		if (main->pipe_tools.child == 0)
	// 		{
	// 			if (i == 0)
	// 			{
	// 					if (main->cmd_table[i].tools.y_exe && !main->cmd_table[i].tools.y_redir)
	// 					{
	// 						ft_dup_fds(main, i);
	// 						write(2,"1redir here\n",12);
	// 						execute_tools(&main->cmd_table[i]);
	// 						if (execve(main->cmd_table[i].cmd_path, main->cmd_table[i].exe_tools.arguments, NULL) == -1)
	// 						{
	// 							write(2,"f mini-chan🌸: ",18);
	// 							write(2,main->cmd_table[i].exe_tools.arguments[0],ft_strlen(main->cmd_table[i].exe_tools.arguments[0]));
	// 							write(2,": command not found\n",21);
	// 							exit(1);
	// 						}
	// 					}
	// 					else if(main->cmd_table[i].tools.y_redir)
	// 					{
	// 						write(2,"2redir here\n",11);
	// 						redir(&main->cmd_table[i]);
	// 					}
	// 					else
	// 					{
	// 						run_builtn(&main->cmd_table[i]);
	// 						exit(0);
	// 					}
	// 			}
	// 			else if ((i == main->pipe_tools.p_num) && main->pipe_tools.child == 0)
	// 			{
	// 					if (main->cmd_table[i].tools.y_exe && !main->cmd_table[i].tools.y_redir)
	// 					{
	// 						ft_dup_fds(main, i);
	// 						write(2,"3redir here\n",12);
	// 						execute_tools(&main->cmd_table[i]);
	// 						if (execve(main->cmd_table[i].cmd_path, main->cmd_table[i].exe_tools.arguments, NULL) == -1)
	// 						{
	// 							write(2,"l mini-chan🌸: ",18);
	// 							write(2,main->cmd_table[i].exe_tools.arguments[0],ft_strlen(main->cmd_table[i].exe_tools.arguments[0]));
	// 							write(2,": command not found\n",21);
	// 							exit(1);
	// 						}
	// 					}
	// 					else if(main->cmd_table[i].tools.y_redir)
	// 					{
	// 						write(2,"4redir here\n",11);
	// 						redir(&main->cmd_table[i]);
	// 					}
	// 					else
	// 					{
	// 						run_builtn(&main->cmd_table[i]);
	// 						exit(0);
	// 					}
	// 			}
	// 			else
	// 			{
	// 					if (main->cmd_table[i].tools.y_exe && !main->cmd_table[i].tools.y_redir) 
	// 					{
	// 						write(2,"5redir here\n",11);
	// 						ft_dup_fds(main, i);
	// 						execute_tools(&main->cmd_table[i]);
	// 						if (execve(main->cmd_table[i].cmd_path, main->cmd_table[i].exe_tools.arguments, NULL) == -1)
	// 						{
	// 							write(2,"m mini-chan🌸: ",18);
	// 							write(2,main->cmd_table[i].exe_tools.arguments[0],ft_strlen(main->cmd_table[i].exe_tools.arguments[0]));
	// 							write(2,": command not found\n",21);
	// 							exit(1);
	// 						}
	// 					}
	// 					else if(main->cmd_table[i].tools.y_redir)
	// 					{
	// 						write(2,"6redir here\n",11);
	// 						redir(&main->cmd_table[i]);
	// 					}
	// 					else
	// 					{
	// 						run_builtn(&main->cmd_table[i]);
	// 						exit(0);
	// 					}
	// 			}
	// 		}
	// 		else
	// 		{
	// 			if (i < main->pipe_tools.p_num)
	// 			{
	// 				if (close(main->pipe_tools.fds[i][1]) == -1)
	// 					perror("first close\n");
	// 			}
	// 			if (i > 0)
	// 			{
	// 				if (close(main->pipe_tools.fds[i - 1][0]) == -1)
	// 					perror(". sec close \n");
	// 			}
	// 		}
	// 	}
	// }
	// 	i = 0;
	// 	while (i < 3)
	// 	{
	// 		waitpid(-1, &main->pipe_tools.status, 0);
	// 		i++;
	// 	}
	return (0);
}
