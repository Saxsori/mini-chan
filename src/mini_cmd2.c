/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:39:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/24 12:41:51 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	mini_export(t_shell_chan *main)
{
	(void) main;
	printf("export was here\n");
	return (1);
}

int	mini_unset(t_shell_chan *main)
{
	(void) main;
	printf("unset was here\n");
	return (1);
}

int	mini_env(t_shell_chan *main)
{
	(void) main;
	printf("env was here\n");
	return (1);
}
