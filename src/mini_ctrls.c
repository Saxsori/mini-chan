/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ctrls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:39:55 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:23:02 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

/*
when readline return NULL it means that ctrl+d was pressed
*/
void	ctrl_d(t_shell_chan *main)
{
	if (!main->cmd_line)
	{
		printf(BCYN"exit\n"BWHT);
		ft_exit (main, 0);
	}
}

/*
? rl_line_buffer -> the line gathered so far form readline
? rl_on_new_line(); -> moving onto a new line 
? rl_replace_line("", 0); -> Replace the contents 
?					of rl_line_buffer with text (NULL)
? rl_redisplay -> Change what's displayed on the 
?	screen to reflect the current contents of rl_line_buffer
*/
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
	{
		new_prompt('c');
		g_status = 7;
	}
}

void	ctrl_ign(int i)
{
	(void)i;
	if (rl_end > 0)
	{
		write(1, "\nQuit\n", 7);
		exit(0);
	}
	else
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
ctrl+/ -> create the signal SIGQUIT 
	so when this signal is recieved 
	it should be ignored
ctrl+c -> create the signal SIGINT
	so when this signal is recieved
	it should create a new line
	means new prombt should be created
	// printf("%d\n", rl_end);
	// if (!rl_end)
	// 	signal(SIGQUIT, SIG_IGN);
	// else
	// 	signal(SIGQUIT, SIG_DFL);
*/
void	mini_sig(void)
{
	signal(SIGQUIT, ctrl_ign);
	signal(SIGINT, ctrl_c);
}
