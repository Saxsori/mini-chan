/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 06:37:12 by dfurneau          #+#    #+#             */
/*   Updated: 2022/08/08 06:16:37 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	redir_exe(t_mini_cmd *cmd)
{
	//todo path == null
	path_finder(cmd);
	if(execve(cmd->cmd_path, cmd->redir.arguments, NULL) == -1)
	{
		write(2,"Command not found\n",19);
		exit(1);
	}
}

void	redir(t_mini_cmd *cmd)
{
	// printf("arg redir  %d \n",cmd->redir.redir_tools.num_redir);
	// printf("cmd name %s  %s\n",cmd->redir.command, cmd->cmd_path);
	int	i;
	int fd;
	pid_t child;
	int status;

	// printf("%s abrab cmd name\n",cmd->redir.command);
	i = 0;
	child = fork();
	if(child == 0)
	{
		while(i < cmd->redir.redir_tools.num_redir)
		{
			if(!ft_strncmp(cmd->redir.redir[i],">",ft_strlen(">")))
			{
				if(access(cmd->redir.files[i], F_OK) == -1)
					fd = open(cmd->redir.files[i], O_WRONLY| O_TRUNC| O_CREAT, 0644);
				else
					fd = open(cmd->redir.files[i], O_WRONLY| O_TRUNC| O_CREAT, 0644);
				dup2(fd, STDOUT_FILENO);
				close(fd);
				
			}
			else if(!ft_strncmp(cmd->redir.redir[i],"<",ft_strlen("<")))
			{
				if(access(cmd->redir.files[i], F_OK) == 0)
					fd = open(cmd->redir.files[i], O_RDONLY);
				else
				{
					write(1, cmd->redir.files[i],ft_strlen(cmd->redir.files[i]));
					write(1,"No such file or directory", 26);
					exit(127);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			else if(!ft_strncmp(cmd->redir.redir[i],">>",ft_strlen(">>")))
			{
				if(access(cmd->redir.files[i], F_OK) == -1)
					fd = open(cmd->redir.files[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
				else
					fd = open(cmd->redir.files[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			else if(!ft_strncmp(cmd->redir.redir[i],"<<",ft_strlen("<<")))
			{
				char *eof;
				while(3)
				{
					eof = readline("> ");
					// if(ft_strncmp(eof,cmd->redir.files[0],ft_strlen(eof)))
					// {
					// 	redir(cmd);
					// }
					if(!ft_strncmp(eof,cmd->redir.files[0],ft_strlen(eof)))
					{
						redir_exe(cmd);
						// exit(0);
					}	
				}
			}
			
			i++;
		}
		if(!is_command(cmd->redir.command))
		{
			redir_exe(cmd);
		}
		else if (is_command(cmd->redir.command))
		{
			run_builtn(cmd);
			exit(0);
		}
	}
	else
		waitpid(-1, &status, 0);
}