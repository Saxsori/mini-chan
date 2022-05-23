
#include "../mini_chan.h"

/*
when readline return NULL it means that ctrl+d was pressed
*/
void	ctrl_d(t_shell_chan *main)
{
	if (!main->cmd_line)
	{
		printf("\n");
		printf("exit\n");
		exit (0);
	}
}

void	ctrl_c(int c)
{
	(void)c;

	printf ("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

/*
ctrl+/ -> create the signal SIGQUIT 
	so when this signal is recieved 
	it should be ignored
ctrl+c -> create the signal SIGINT
	so when this signal is recieved
	it should create a new line
	means new prombt should be created
*/
void	mini_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
}
