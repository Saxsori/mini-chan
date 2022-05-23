
#include "../mini_chan.h"

void	init_shell_chan(t_shell_chan *main)
{
	main->cmd_line = 0;
	main->cmd_num = 0;
}

void	re_init_shell_chan(t_shell_chan *main)
{
	main->cmd_num = 0;
}
