
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

void	init_mini_cmd(t_mini_cmd *cmd)
{
	cmd->arguments = NULL;
	cmd->option = NULL;
	cmd->tools.arg_num = 0;
	cmd->tools.opt_num = 0;
	cmd->tools.arg_index = -1;
	cmd->tools.y_op = 0;
}
