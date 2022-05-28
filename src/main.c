/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:41:51 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/28 17:50:38 by aaljaber         ###   ########.fr       */
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
	int	k;

	i = -1;
	while (++i < main->cmd_num)
	{
		init_mini_cmd(&main->cmd_table[i], main);
		check_opt(&main->cmd_table[i]);
		check_arg(&main->cmd_table[i]);
	}
	i = -1;
	while (++i < main->cmd_num)
	{
		k = -1;
		while (++k < main->cmd_table->tools.opt_num)
		{
			printf("opt%s\n", main->cmd_table[i].option[k]);
		}
		k = -1;
		while (++k < main->cmd_table->tools.arg_num)
		{
			printf("arg%s\n", main->cmd_table[i].arguments[k]);
		}
		printf("1:%d\n", main->cmd_num);
		printf("2:%d\n", main->cmd_table[i].main->cmd_num);
	}
}

// printf("cmd_count%d\n", main->cmd_num);
/*
? command line parts splitting and checking 
? depending on the command itself
? if this command was vaild then find it's part and run the command
? else there is something wrong with this command  
! run_cmd should be fixed by boo depending on the processe if there
! is pipes
// int i;
// i = -1;
// while (++i < main->cmd_num)
// 	printf("%s\n", main->first_split[i]);
// printf("%d\n", main->cmd_num);
*/
int	find_command(t_shell_chan *main)
{
	mini_tools(main);
	command_name(main);
	if (command_name(main))
	{
		check_cmd_parts(main);
		return (run_cmd(main));
	}
	return (0);
}

/*
? ctrld -> if cmd_line return null that's mean that
? it's the end of the line and it could happen  
? when ctrl+d pressed
*/
int	main(int argc, char **argv, char **env)
{
	t_shell_chan	main;

	(void) argc;
	(void) argv;
	init_shell_chan(&main);
	mini_sig();
	while (42)
	{
		main.cmd_line = readline(BMAG"mini-chan🌸$ "BBLU);
		ctrl_d(&main);
		re_init_shell_chan(&main);
		create_envar_list(&main, env);
		if (find_command(&main))
			main.exit_status = EXIT_SUCCESS;
		else
			main.exit_status = EXIT_FAILURE;
	}
	return (0);
}
