/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 07:17:42 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/29 02:55:14 by dfurneau         ###   ########.fr       */
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
void	redir(t_mini_cmd *cmd)
{
	int	i;
	int fd;
	pid_t child;
	int status;
	i = 0;
	
		if(cmd->main->cmd_num > 1)
		{
			redir_mix(cmd);
		}
		else if (cmd->main->cmd_num == 1)
		{
			write(2,"only redir\n",11);
			child = fork();
			if(child == 0)
			{
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
						// while(!ft_strncmp(cmd->redir.redir[i],"<<",ft_strlen("<<")))
						// 	i++;
						char *eof;
						int fd[2];
						int stat;
						if(pipe(fd) < 0)
							perror("pipe error");
						pid_t child;
						child = fork();
						if(child == 0)
						{
							while(3)
							{
								eof = readline("> ");
								if(!ft_strncmp(eof,cmd->redir.files[i],ft_strlen(eof)))
									break;
								write(fd[1],eof,ft_strlen(eof));
								write(fd[1],"\n",1);
							}
							close(fd[1]);
							dup2(fd[0], STDIN_FILENO);
							close(fd[0]);
							// if(!ft_strncmp(cmd->redir.command, "cat", ft_strlen("cat")))
								redir_exe(cmd);
						}
						else {
							close(fd[0]);
							close(fd[1]);
							waitpid(-1, &stat, 0);
						}
					}
					
					i++;
				}
			
				if(!is_command(cmd->redir.command) && !ft_strncmp(cmd->redir.redir[i], "cat", ft_strlen("cat")))//&& !ft_strncmp(cmd->redir.redir[i], "<<", ft_strlen("<<") todo if command is "cat"
				{
					write(2,"9exe  here\n",12);
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
}