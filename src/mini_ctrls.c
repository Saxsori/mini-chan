/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ctrls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:39:55 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/07 21:23:58 by aaljaber         ###   ########.fr       */
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
		// rl_replace_line("", 0);
	}
	else
	{
		printf ("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
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

// void	ctrl_ign(int i)
// {
// 	// (void)i;
// 	if (rl_line_buffer)
// 		printf("%s\n", rl_line_buffer);
// 	else
// 		printf("NULL\n");
// 	if (!ft_strncmp(rl_line_buffer, "^\'", 2))
// 		SIG_IGN(i);
// }

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
