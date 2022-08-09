/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 06:37:12 by dfurneau          #+#    #+#             */
/*   Updated: 2022/08/09 15:09:56 by balnahdi         ###   ########.fr       */
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
					if(!ft_strncmp(eof,cmd->redir.files[i],ft_strlen(eof)))
						break;
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