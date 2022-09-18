/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:49:49 by dfurneau          #+#    #+#             */
/*   Updated: 2022/09/18 15:45:10 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	redir_in(t_mini_cmd *cmd, int i)
{
	struct stat	per;

	if (cmd->redir.files[i][0] == '\0')
	{
		errmsg(cmd->redir.files[i], NO_F_DIR);
		exit(1);
	}
	if (access(cmd->redir.files[i], F_OK) == -1)
		cmd->redir.redir_tools.fd_redir = open(cmd->redir.files[i], \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (access(cmd->redir.files[i], F_OK) == 0)
		cmd->redir.redir_tools.fd_redir = open(cmd->redir.files[i], \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
	stat(cmd->redir.files[i], &per);
	if ((per.st_mode & S_IWUSR))
	{
		if (dup2(cmd->redir.redir_tools.fd_redir, STDOUT_FILENO) < 0)
			perror("dup >");
		close(cmd->redir.redir_tools.fd_redir);
	}
	else
	{
		errmsg(cmd->redir.files[i], PER_ERR);
		exit(126);
	}
}

void	redir_out(t_mini_cmd *cmd, int i)
{
	struct stat	per;

	if (access(cmd->redir.files[i], F_OK) == 0)
		cmd->redir.redir_tools.fd_redir = open(cmd->redir.files[i], \
		O_RDONLY);
	else
	{
		errmsg(cmd->redir.files[i], NO_F_DIR);
		exit(1);
	}
	stat (cmd->redir.files[i], &per);
	if (per.st_mode & S_IRUSR)
	{
		if (dup2(cmd->redir.redir_tools.fd_redir, STDIN_FILENO) < 0)
			perror("dup <");
		close(cmd->redir.redir_tools.fd_redir);
	}
	else
	{
		errmsg(cmd->redir.files[i], PER_ERR);
		exit(126);
	}
}

void	redir_append(t_mini_cmd *cmd, int i)
{
	struct stat	per;

	if (cmd->redir.files[i][0] == '\0')
	{
		errmsg(cmd->redir.files[i], NO_F_DIR);
		exit(1);
	}
	if (access(cmd->redir.files[i], F_OK) == -1)
		cmd->redir.redir_tools.fd_redir = open(cmd->redir.files[i], \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		cmd->redir.redir_tools.fd_redir = open(cmd->redir.files[i], \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	stat (cmd->redir.files[i], &per);
	if (per.st_mode & S_IWUSR)
	{
		if (dup2(cmd->redir.redir_tools.fd_redir, STDOUT_FILENO) < 0)
			perror("dup >>");
		close(cmd->redir.redir_tools.fd_redir);
	}
	else
	{
		errmsg (cmd->redir.files[i], PER_ERR);
		exit(126);
	}
}
