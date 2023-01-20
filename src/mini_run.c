/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:22:19 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

/*
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
	get_path(main);
	if (main->cmd_num == 1)
	{
		if (main->cmd_table->tools.y_redir)
			run_one_redir(main);
		else if (is_command(main->cmd_table[0].name))
		{
			g_status = run_builtn(&main->cmd_table[0]);
			return (g_status);
		}
		else if (!is_command(main->cmd_table[0].name))
		{
			execute_tools(&main->cmd_table[0]);
			mini_execute(&main->cmd_table[0]);
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
