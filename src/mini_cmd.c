/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:47:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/24 20:59:34 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	mini_cd(t_shell_chan *main)
{
	(void) main;
	printf("cd was here\n");
	return (1);
}

int	mini_echo(t_shell_chan *main)
{
	(void) main;
	printf("echo was here\n");
	return (1);
}

int	mini_pwd(t_shell_chan *main)
{
	
}

int	mini_exit(t_shell_chan *main)
{
	(void) main;
	printf("exit was here\n");
	return (1);
}
