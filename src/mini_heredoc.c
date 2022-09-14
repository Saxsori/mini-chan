/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 08:28:05 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 14:43:14 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	is_null(char *file)
{
	if (file[0] == '\f')
		return (1);
	return (0);
}

void	redir_heredoc_loop(t_mini_cmd *cmd)
{
	char	*eof;
	int		i;

	i = 0;
	while (3)
	{
		eof = readline("> ");
		cmd->redir.redir_tools.ld = 0;
		if (!ft_strncmp(eof, cmd->redir.files[i], ft_strlen(eof)) || \
		(eof[0] == '\0' && is_null(cmd->redir.files[i])))
		{
			i++;
			if (i == cmd->redir.redir_tools.num_redir - 1)
				cmd->redir.redir_tools.ld = 1;
		}
		if (i == cmd->redir.redir_tools.num_redir - 1 && \
		cmd->redir.redir_tools.ld == 0)
		{
			write(cmd->redir.redir_tools.fd[0][1], eof, ft_strlen(eof));
			write(cmd->redir.redir_tools.fd[0][1], "\n", 1);
		}
		if (i == cmd->redir.redir_tools.num_redir)
			break ;
	}
}

void	redir_init_fd(t_mini_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->redir.redir_tools.fd = (int **)malloc(sizeof(int *));
	cmd->redir.redir_tools.fd[0] = (malloc(sizeof(int ) * 2));
	while (i < 2)
	{
		cmd->redir.redir_tools.fd[0][i] = i;
		i++;
	}
}

void	redir_heredoc(t_mini_cmd *cmd)
{
	redir_init_fd(cmd);
	if (pipe(cmd->redir.redir_tools.fd[0]) < 0)
		perror("pipe error");
	cmd->redir.redir_tools.child = fork();
	if (cmd->redir.redir_tools.child == 0)
	{
		printf("check2\n");
		redir_heredoc_loop(cmd);
		close(cmd->redir.redir_tools.fd[0][1]);
		dup2(cmd->redir.redir_tools.fd[0][0], STDIN_FILENO);
		close(cmd->redir.redir_tools.fd[0][0]);
		write(2, "vooooooo\n", 10);
		if (cmd->redir.command)
			redir_exe(cmd);
		else
			exit(0);
	}
	else
	{
		close(cmd->redir.redir_tools.fd[0][0]);
		close(cmd->redir.redir_tools.fd[0][1]);
		waitpid(-1, &cmd->redir.redir_tools.status, 0);
	}
}
