/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:39:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/26 10:46:01 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	mini_export(t_mini_cmd *cmd)
{
	(void) cmd;
	printf("export was here\n");
	return (1);
}

int	mini_unset(t_mini_cmd *cmd)
{
	(void) cmd;
	printf("unset was here\n");
	return (1);
}

int	mini_env(t_mini_cmd *cmd)
{
	(void) cmd;
	printf("env was here\n");
	return (1);
}
