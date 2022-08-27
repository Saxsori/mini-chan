/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 11:06:59 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/26 20:05:10 by aaljaber         ###   ########.fr       */
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
// 	// i = -1;
// 	// while (++i < main->cmd_num)
// 	// {
// 	// 	k = -1;
// 	// 	while (++k < main->cmd_table->tools.opt_num)
// 	// 	{
// 	// 		printf("opt %s\n", main->cmd_table[i].option[k]);
// 	// 	}
// 	// 	k = -1;
// 	// 	while (++k < main->cmd_table->tools.arg_num)
// 	// 	{
// 	// 		printf("arg %s\n", main->cmd_table[i].arguments[k]);
// 	// 	}
// 	// }
*/
void	check_cmd_parts(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		check_opt(&main->cmd_table[i]);
		check_arg(&main->cmd_table[i]);
	}
}

void	check_isbuiltin(t_shell_chan *main)
{
	int		i;
	char	**split;

	i = -1;
	printf("here\n");
	while (++i < main->cmd_num)
	{
		split = ft_split(main->first_split[i], ' ');
		if (split)
		{
			if (is_command(split[0]))
				main->cmd_table[i].tools.y_exe = 0;
			else
				main->cmd_table[i].tools.y_exe = 1;
			squaredstr_free(split);
		}
	}
}

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
?

*/
int	find_command(t_shell_chan *main)
{
	// int	i;
	// int	k;

	first_cmd_split(main);
	if (main->exit_status == 2)
		return (2);
	expand_tools(main);
	redir_tools(main);
	if (quotes_checker(main))
	{
		// printf("here\n");
		if (pre_redir(main) == 2)
			return (2);
		pre_quote(main);
		expand_envar(main);
		parse_echo_case(main);
		remove_quote(main);
		check_isbuiltin(main);
		// i = -1;
		// while (++i < main->cmd_num)
		// {
		// 	printf("(%s)", main->first_split[i]);
		// 	printf(" - r %d", main->cmd_table[i].tools.y_redir);
		// 	printf(" - e %d\n", main->cmd_table[i].tools.y_exe);
		// }
		split_redir(main);
		split_command(main);
		if (main->exit_status == 2)
			return (2);
		command_name(main);
		check_cmd_parts(main);
	// 	i = -1;
	// 	while (++i < main->cmd_num)
	// 	{
	// 		if (main->cmd_table[i].tools.y_redir)
	// 		{
	// 			printf("r command->>> %s\n", main->cmd_table[i].redir.command);
	// 			k = -1;
	// 			while (++k < main->cmd_table[i].redir.redir_tools.num_arg + 1)
	// 				printf("r arg->>> %s\n", main->cmd_table[i].redir.arguments[k]);
	// 			k = -1;
	// 			while (++k < main->cmd_table[i].redir.redir_tools.num_redir)
	// 				printf("r redir->>> %s\n", main->cmd_table[i].redir.redir[k]);
	// 			k = -1;
	// 			while (++k < main->cmd_table[i].redir.redir_tools.num_file)
	// 				printf("r files->>> %s\n", main->cmd_table[i].redir.files[k]);
	// 		}
		// }
		return (run_cmd(main));
	}
	// else
		//free first_split .. cmd_table .. expand_tools .. redir_tools
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
		VALGRIND_DO_LEAK_CHECK;
	}
	// free envar
	return (0);
}
