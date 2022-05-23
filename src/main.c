
#include "../mini_chan.h"

int mini_cd(t_shell_chan *main)
{
	(void) main;
	printf("cd was here\n");
	return (1);
}

// int	find_command(t_shell_chan *main)
// {
// 	if (!ft_strncmp(main->cmd_line, "cd", strlen(main->cmd_line)))
// 		return (mini_cd(main));
// 	return (0);
// }
void	cmd_counter(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(main->cmd_line))
	{
		if (main->cmd_line[i] == '|')
			main->cmd_num++;
	}
	main->cmd_num++;
}

void	mini_tools(t_shell_chan *main)
{
	cmd_counter(main);
	main->cmd_table = (t_mini_cmd *)malloc(main->cmd_num * sizeof(t_mini_cmd));
	if (cmd_counter > 1)
		main->cmd_split = ft_split(main->cmd_line, '|');
	
}

	// printf("cmd_count%d\n", main->cmd_num);
int	find_command(t_shell_chan *main)
{
	mini_tools(main);

	return (1);
}

/*
 ctrld -> if cmd_line return null that's mean that
 it's the end of the line and it could happen  
 when ctrl+d pressed
*/
int	main(void)
{
	t_shell_chan	main;

	init_shell_chan(&main);
	while (42)
	{
		main.cmd_line = readline(BBLU"mini-chan$ "BYEL);
		ctrl_d(&main);
		re_init_shell_chan(&main);
		if (find_command(&main))
			printf ("1\n");
		
		// if (find_command(&main))
		// 	printf ("1\n");
		// else
		// 	printf ("0\n");
	}
	return (0);
}
