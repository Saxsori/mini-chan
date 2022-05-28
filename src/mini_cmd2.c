/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:39:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/28 18:07:04 by aaljaber         ###   ########.fr       */
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
	print_envar_list(cmd->main->head_envar);
	return (1);
}
