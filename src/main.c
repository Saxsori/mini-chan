/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:41:51 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/24 19:10:03 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"


/*
! b4 u put them in their places check for the qoutes
! check for the environmental variables ^.^
! check for opt is postponded till know if u may get '-' when it's arg
// check_opt(main);
// void	check_opt(t_shell_chan *)
// if (ft_strchr(main->cmd_table[i].split[k], '-'))
*/
void	check_cmd_parts(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		init_mini_cmd(&main->cmd_table[i]);
		check_opt(&main->cmd_table[i]);
		check_arg(&main->cmd_table[i]);
	}
}

// printf("cmd_count%d\n", main->cmd_num);
/*
? command line parts splitting and checking 
? depending on the command itself
? if this command was vaild then find it's part and run the command
? else there is something wrong with this command  
*/
int	find_command(t_shell_chan *main)
{
	int	i;

	i = -1;
	mini_tools(main);
	if (command_name(main))
	{
		check_cmd_parts(main);
		run_cmd(main);
		return (1);
	}
	else
		ft_putstr_fd("this commands is invalid\n", 1);
	return (0);
}

/*
? ctrld -> if cmd_line return null that's mean that
? it's the end of the line and it could happen  
? when ctrl+d pressed
*/
int	main(void)
{
	t_shell_chan	main;

	init_shell_chan(&main);
	mini_sig();
	while (42)
	{
		main.cmd_line = readline(BBLU"mini-chan$ "BYEL);
		ctrl_d(&main);
		re_init_shell_chan(&main);
		if (find_command(&main))
			printf ("1\n");
	}
	return (0);
}
