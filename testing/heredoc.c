#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac,char *av[])
{
	int i =0;
	char *cmdline;
	while(av[i])
	{
		if(av[1][i] == '{')
		{
			while(1)
			{
				cmdline = readline("> ");
				printf("here %s == %s\n",cmdline,av[2]);
				if(!strncmp(cmdline,av[2],2))
				{
					break;
					exit(0);
				}
			}
		}
		i++;
	}
}