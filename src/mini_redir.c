/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 07:17:42 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/29 14:28:40 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"
#include <stdio.h>
// #include <sys/_types/_pid_t.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void	redir_exe(t_mini_cmd *cmd)
{
	//todo path == null
	if (cmd->redir.command)
	{
		path_finder(cmd);
	}
	if (execve(cmd->cmd_path, cmd->redir.arguments, NULL) == -1)
	{
		write (2, "Command not found\n", 19);
		exit(1);
	}
}

void	redir_mix(t_mini_cmd *cmd)
{
	int	i;
	i = 0;
	int fd;
		while(i < cmd->redir.redir_tools.num_redir )
		{
			if(!ft_strncmp(cmd->redir.redir[i],">",ft_strlen(">")))
			{
				if(access(cmd->redir.files[i], F_OK) == -1)
					fd = open(cmd->redir.files[i], O_WRONLY| O_TRUNC| O_CREAT, 0644);
				else
					fd = open(cmd->redir.files[i], O_WRONLY| O_TRUNC| O_CREAT, 0644);
				write(2,"dup > here\n",11);
				if(dup2(fd, STDOUT_FILENO) < 0)
					perror("dup >");
				close(fd);
			}
			else if(!ft_strncmp(cmd->redir.redir[i],"<",ft_strlen("<")))
			{
				if(access(cmd->redir.files[i], F_OK) == 0)
				{
						fd = open(cmd->redir.files[i], O_RDONLY);
						write(1,"\n here1 \n",9);
				}
				else
				{
					write(2, cmd->redir.files[i],ft_strlen(cmd->redir.files[i]));
					write(2,"No such file or directory\n", 26);
					exit(127);
				}
				write(2,"dup < here\n",11);
				if(dup2(fd, STDIN_FILENO) < 0)
					perror("dup <");
				close(fd);
			}
			else if(!ft_strncmp(cmd->redir.redir[i],">>",ft_strlen(">>")))
			{
				if(access(cmd->redir.files[i], F_OK) == -1)
					fd = open(cmd->redir.files[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
				else
					fd = open(cmd->redir.files[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
				write(2,"dup >> here\n",12);				
				if(dup2(fd, STDOUT_FILENO) < 0)
					perror("dup >>");
				close(fd);
			}
			else if(!ft_strncmp(cmd->redir.redir[i],"<<",ft_strlen("<<")))
			{
				char *eof;
				while(3)
				{
					eof = readline("> ");
					if(!ft_strncmp(eof,cmd->redir.files[i],ft_strlen(eof)))
						break;
				}
			}
			
			i++;
		}
		if(!is_command(cmd->redir.command))
		{
			write(2,"exe   here\n",12);
			redir_exe(cmd);
		}
		else if (is_command(cmd->redir.command))
		{
			run_builtn(cmd);
			exit(0);
		}
}

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

void	redir_sign(t_mini_cmd *cmd, int i)
{
	if (!ft_strncmp(cmd->redir.redir[i], ">", ft_strlen(">")))
		redir_in(cmd, i);
	else if (!ft_strncmp(cmd->redir.redir[i], "<", ft_strlen("<")))
		redir_out(cmd, i);
	else if (!ft_strncmp(cmd->redir.redir[i], ">>", ft_strlen(">>")))
		redir_append(cmd, i);
}

void	redir(t_mini_cmd *cmd)
{
	int		i;

	i = 0;
	cmd->redir.redir_tools.child = fork();
	if (cmd->redir.redir_tools.child == 0)
	{
		while (i < cmd->redir.redir_tools.num_redir)
		{
			redir_sign(cmd, i);
			i++;
		}
		if (!is_command(cmd->redir.command))
		{
			write(2, "9exe  here\n", 12);
			redir_exe(cmd);
		}
		else if (is_command(cmd->redir.command))
		{
			run_builtn(cmd);
			exit(0);
		}
	}
	else
		waitpid(-1, &cmd->redir.redir_tools.status, 0);
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
		if (!ft_strncmp(eof, cmd->redir.files[i], ft_strlen(eof)))
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
	if (pipe(cmd->redir.redir_tools.fd[0]) < 0)
		perror("pipe error");
	cmd->redir.redir_tools.child = fork();
	if (cmd->redir.redir_tools.child == 0)
	{
		redir_heredoc_loop(cmd);
		close(cmd->redir.redir_tools.fd[0][1]);
		dup2(cmd->redir.redir_tools.fd[0][0], STDIN_FILENO);
		close(cmd->redir.redir_tools.fd[0][0]);
		redir_exe(cmd);
	}
	else
	{
		close(cmd->redir.redir_tools.fd[0][0]);
		close(cmd->redir.redir_tools.fd[0][1]);
		waitpid(-1, &cmd->redir.redir_tools.status, 0);
	}
}
