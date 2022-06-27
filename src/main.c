/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:41:51 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/27 07:44:17 by aaljaber         ###   ########.fr       */
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
	// 	}
	// 	printf("opt num %d\n", main->cmd_table->tools.opt_num);
	// 	printf("arg num %d\n", main->cmd_table->tools.arg_num);
	// 	// printf("1:%d\n", main->cmd_num);
	// 	// printf("2:%d\n", main->cmd_table[i].main->cmd_num);
*/
void	check_cmd_parts(t_shell_chan *main)
{
	int	i;
	// int	k;

	i = -1;
	while (++i < main->cmd_num)
	{
		init_mini_cmd(&main->cmd_table[i], main);
		printf ("1here\n");
		check_opt(&main->cmd_table[i]);
		check_arg(&main->cmd_table[i]);
	}
	// i = -1;
	// while (++i < main->cmd_num)
	// {
	// 	k = -1;
	// 	while (++k < main->cmd_table->tools.opt_num)
	// 	{
	// 		printf("opt %s\n", main->cmd_table[i].option[k]);
	// 	}
	// 	k = -1;
	// 	while (++k < main->cmd_table->tools.arg_num)
	// 	{
	// 		printf("arg %s\n", main->cmd_table[i].arguments[k]);
	// 	}
	// }
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
! after splitting | check quotes for each command and then if it was correct
! split command parts then expand
*/
int	find_command(t_shell_chan *main)
{
	int	i;

	first_cmd_split(main);
	if (main->exit_status == 2)
		return (2);
	expand_tools(main);
	if (quotes_checker(main))
	{
		expand_envar(main);
		parse_echo_case(main);
		remove_quote(main);
		i = -1;
		while (++i < main->cmd_num)
			printf("(%s)\n", main->first_split[i]);
		split_command(main);
		if (main->exit_status == 2)
			return (2);
		if (command_name(main))
		{
			check_cmd_parts(main);
			return (run_cmd(main));
		}
	}
	return (0);
}

/*
? ctrld -> if cmd_line return null that's mean that
? it's the end of the line and it could happen  
? when ctrl+d pressed
		// printf("%d\n", main.exit_status);
*/
int	main(int argc, char **argv, char **env)
{
	t_shell_chan	main;

	(void) argc;
	(void) argv;
	init_shell_chan(&main);
	mini_sig();
	create_envar_list(&main, env);
	printf(BCYN "\nThis shell has been raised (created) with\nunconditional love (anger), in a hope to be \na successful happy shell in the future ^◡^ \n");
	while (42)
	{
		main.cmd_line = readline(BMAG"mini-chan🌸$ "BBLU);
		ctrl_d(&main);
		if (!check_cmd_line(main.cmd_line))
			new_prompt(1);
		else if (check_cmd_line(main.cmd_line))
			main.exit_status = find_command(&main);
		re_init_shell_chan(&main);
	}
	//free envar
	return (0);
}
