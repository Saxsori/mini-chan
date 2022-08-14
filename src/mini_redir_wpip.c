#include "../mini_chan.h"
#include <stdio.h>

void	redir_pip(t_shell_chan *main,t_mini_cmd *cmd, int i)
{
	printf("arg redir  %d \n",cmd->redir.redir_tools.num_redir);
	int	k;
	int fd;
	// pid_t child;
	// int status;
	k = 0 ;
	// child = fork();
	// if(child == 0)
	// {
		while(k < main->cmd_table[i].redir.redir_tools.num_redir)
		{
			if(!ft_strncmp(main->cmd_table[i].redir.files[k],">",ft_strlen(">")))
			{
				if(access(main->cmd_table[i].redir.files[k], F_OK) == -1)
					fd = open(main->cmd_table[i].redir.files[k], O_WRONLY| O_TRUNC| O_CREAT, 0644);
				else
					fd = open(main->cmd_table[i].redir.files[k], O_WRONLY| O_TRUNC| O_CREAT, 0644);
				write(2,"dup > here\n",11);
				if(dup2(fd, STDOUT_FILENO) < 0)
					perror("dup >");
				close(fd);
			}
			else if(!ft_strncmp(main->cmd_table[i].redir.files[k],"<",ft_strlen("<")))
			{
				if(access(main->cmd_table[i].redir.files[k], F_OK) == 0)
				{
						fd = open(main->cmd_table[i].redir.files[k], O_RDONLY);
						write(1,"\n here1 \n",9);
				}
				else
				{
					write(2, main->cmd_table[i].redir.files[k],ft_strlen(main->cmd_table[i].redir.files[k]));
					write(2,"No such file or directory\n", 26);
					exit(127);
				}
				write(2,"dup < here\n",11);
				if(dup2(fd, STDIN_FILENO) < 0)
					perror("dup <");
				close(fd);
			}
			else if(!ft_strncmp(main->cmd_table[i].redir.files[k],">>",ft_strlen(">>")))
			{
				if(access(main->cmd_table[i].redir.files[k], F_OK) == -1)
					fd = open(main->cmd_table[i].redir.files[k], O_WRONLY | O_APPEND | O_CREAT, 0644);
				else
					fd = open(main->cmd_table[i].redir.files[k], O_WRONLY | O_APPEND | O_CREAT, 0644);
				write(2,"dup >> here\n",12);				
				if(dup2(fd, STDOUT_FILENO) < 0)
					perror("dup >>");
				close(fd);
			}
			else if(!ft_strncmp(main->cmd_table[i].redir.files[k],"<<",ft_strlen("<<")))
			{
				char *eof;
				while(3)
				{
					eof = readline("> ");
					if(!ft_strncmp(eof,main->cmd_table[i].redir.files[k],ft_strlen(eof)))
						break;
				}
			}
			
			k++;
		}
		if(!is_command(main->cmd_table[i].redir.command))
		{
			write(2,"\nexe   here\n",12);
			redir_exe(cmd);
		}
		else if (is_command(main->cmd_table[i].redir.command))
		{
			run_builtn(cmd);
			exit(0);
		}
		close(fd);
	// }
	// else
	// 	waitpid(-1, &status, 0);
}