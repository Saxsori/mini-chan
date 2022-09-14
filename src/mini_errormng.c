/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_errormng.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:07:16 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 10:18:50 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

// void	mini_errmng(t_shell_chan *main, int op)
// {
// 	if (op == 1)
// 		printf("mini-chan🌸: %s: ",main->cmd_table->name);
// }

void	exit_msg(t_shell_chan *main, char *status, char **msg)
{
	if (msg)
	{
		printf("mini-chan🌸$: %s\n",*msg);
		free_ptr((void **)msg);
	}
	ft_exit(main, ft_atoi(status));
}

void	errmsg(char *cmd, char *msg)
{
	write(2, BRED, 7);
	write(2, "mini-chan🌸: ", 15);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	write(2, BWHT, 7);
}
