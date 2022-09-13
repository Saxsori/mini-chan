/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_errormng.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:07:16 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/13 12:20:43 by aaljaber         ###   ########.fr       */
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
