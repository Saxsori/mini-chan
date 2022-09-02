/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:49:49 by dfurneau          #+#    #+#             */
/*   Updated: 2022/09/02 08:53:43 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	redir_in(t_mini_cmd *cmd, int i)
{
	if (access(cmd->redir.files[i], F_OK) == -1)
		cmd->redir.redir_tools.fd_redir = open(cmd->redir.files[i], \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		cmd->redir.redir_tools.fd_redir = open(cmd->redir.files[i], \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
	write(2, "dup > here\n", 11);
	if (dup2(cmd->redir.redir_tools.fd_redir, STDOUT_FILENO) < 0)
		perror("dup >");
	close(cmd->redir.redir_tools.fd_redir);
}

void	redir_out(t_mini_cmd *cmd, int i)
{
	if (access(cmd->redir.files[i], F_OK) == 0)
	{
		cmd->redir.redir_tools.fd_redir = open(cmd->redir.files[i], \
		O_RDONLY);
		write(1, "\n here1 \n", 9);
	}
	else
	{
		write(2, cmd->redir.files[i], \
		ft_strlen(cmd->redir.files[i]));
		write(2, "No such file or directory\n", 26);
		exit(127);
	}
	write(2, "dup < here\n", 11);
	if (dup2(cmd->redir.redir_tools.fd_redir, STDIN_FILENO) < 0)
		perror("dup <");
	close(cmd->redir.redir_tools.fd_redir);
}

void	redir_append(t_mini_cmd *cmd, int i)
{
	if (access(cmd->redir.files[i], F_OK) == -1)
		cmd->redir.redir_tools.fd_redir = open(cmd->redir.files[i], \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		cmd->redir.redir_tools.fd_redir = open(cmd->redir.files[i], \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	write(2, "dup >> here\n", 12);
	if (dup2(cmd->redir.redir_tools.fd_redir, STDOUT_FILENO) < 0)
		perror("dup >>");
	close(cmd->redir.redir_tools.fd_redir);
}
