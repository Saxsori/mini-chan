/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:41:51 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/23 18:44:06 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/* 
? passing the command to each command structure 
? and at the same time splitting them from spaces 
? to seprate the command parts 
*/
void	split_command(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
		main->cmd_table[i].split = ft_split(main->first_split[i], ' ');
}

/*
! b4 u put them in their places check for the qoutes
! check for the environmental variables ^.^
! check for opt is postponded till know if u may get '-' when it's arg
// check_opt(main);
// void	check_opt(t_shell_chan *)
// if (ft_strchr(main->cmd_table[i].split[k], '-'))
*/
int	check_cmd_parts(t_shell_chan *main)
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
/*command line parts splitting and checking 
depending on the command itself*/
int	find_command(t_shell_chan *main)
{
	int	i;

	i = -1;
	mini_tools(main);
	if (command_name(main))
	{
		if (check_cmd_parts(main)) //
			run_cmd(main);        //
		else
			ft_putstr_fd("error\n", 1);
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
