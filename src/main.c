/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:11:53 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/18 13:45:04 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	g_status;

/*
// printf("cmd_count%d\n", main->cmd_num);
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
	if (!is_command(main->cmd_table[i].name))
		return (0);

		BOO
? 		first_cmd_split .. split pipes only and fill variables

?? to print the redir (for debug)
		int k;
		int i;
		i = -1;
		while (++i < main->cmd_num)
		{
			if (main->cmd_table[i].tools.y_redir)
			{
				printf("command ----> (%s)\n", main->cmd_table[i].redir.command);
				k = -1;
				if (main->cmd_table[i].redir.redir_tools.num_arg)
				{
					while (++k < main->cmd_table[i].redir.redir_tools.num_arg + 1)
						printf("arg ----> (%s)\n", main->cmd_table[i].redir.arguments[k]);
				}
				else
					printf("no arg\n");
				k = -1;
				while (++k < main->cmd_table[i].redir.redir_tools.num_redir)
					printf("redir ----> (%s)\n", main->cmd_table[i].redir.redir[k]);
				printf("redir num %d\n", main->cmd_table[i].redir.redir_tools.num_redir);
				k = -1;
				while (++k < main->cmd_table[i].redir.redir_tools.num_file)
					printf("files ----> (%s)\n", main->cmd_table[i].redir.files[k]);
			}
		}
*/
int	find_command(t_shell_chan *main)
{
	first_cmd_split(main);
	if (main->exit_status == 2)
		return (2);
	expand_tools(main);
	redir_tools(main);
	if (quotes_checker(main))
	{
		if (pre_redir(main) == 2)
			return (2);
		pre_quote(main);
		expand_envar(main);
		parse_special_null_arg(main);
		remove_quote(main);
		check_isbuiltin(main);
		split_redir(main);
		split_command(main);
		if (main->exit_status == 2)
			return (2);
		command_name(main);
		check_cmd_parts(main);
		return (run_cmd(main));
	}
	else
		return (2);
	return (0);
}

/*
? ctrld -> if cmd_line return null that's mean that
? it's the end of the line and it could happen  
? when ctrl+d pressed
	BOO
?	init_shell_chan init all 
?	mini_sig catch signals
?	create_envar_list create env variables in 2xlinked list ..
 
		// printf("%d\n", main.exit_status);
*/
int	main(int argc, char **argv, char **env)
{
	t_shell_chan	main;

	(void) argc;
	(void) argv;
	g_status = 0;
	init_shell_chan(&main);
	create_envar_list(&main, env);
	printf(BCYN"%s", MINI_CHAN);
	while (42)
	{
		mini_sig();
		main.cmd_line = readline(BMAG"mini-chan🌸$ "BBLU);
		if (main.cmd_line)
			add_history(main.cmd_line);
		ctrl_d(&main);
		if (!check_cmd_line(main.cmd_line))
			new_prompt(1);
		else if (check_cmd_line(main.cmd_line))
			main.exit_status = find_command(&main);
		if (main.exit_status == 2)
			g_status = main.exit_status;
		re_init_shell_chan(&main);
		VALGRIND_DO_LEAK_CHECK ;
	}
	return (0);
}
