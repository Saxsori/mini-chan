/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ctrls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:39:55 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/29 18:12:19 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
when readline return NULL it means that ctrl+d was pressed
*/
void	ctrl_d(t_shell_chan *main)
{
	if (!main->cmd_line)
	{
		printf(BCYN"exit\n"BWHT);
		exit (0);
	}
}

void	new_prompt(int i)
{
	if (i == 1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else
	{
		printf ("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrl_c(int c)
{
	if (c == SIGINT)
		new_prompt('c');
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
