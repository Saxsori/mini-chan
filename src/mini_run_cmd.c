/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_run_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:29:54 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/24 17:15:50 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
! for now this is just working for only one cmd
! this part u should discuss with how it should work
!	with processes 
*/
void	which_command(t_shell_chan *main)
{
	if (!ft_strncmp(main->cmd_table->name, "cd", \
			ft_strlen(main->cmd_table->name)))
		mini_cd(main);
	if (!ft_strncmp(main->cmd_table->name, "echo", \
			ft_strlen(main->cmd_table->name)))
		mini_echo(main);
	if (!ft_strncmp(main->cmd_table->name, "pwd", \
			ft_strlen(main->cmd_table->name)))
		mini_pwd(main);
	if (!ft_strncmp(main->cmd_table->name, "export", \
			ft_strlen(main->cmd_table->name)))
		mini_export(main);
	if (!ft_strncmp(main->cmd_table->name, "unset", \
			ft_strlen(main->cmd_table->name)))
		mini_unset(main);
	if (!ft_strncmp(main->cmd_table->name, "env", \
			ft_strlen(main->cmd_table->name)))
		mini_env(main);
	if (!ft_strncmp(main->cmd_table->name, "exit", \
			ft_strlen(main->cmd_table->name)))
		mini_exit(main);
}

void	run_cmd(t_shell_chan *main)
{
	which_command(main);
}
