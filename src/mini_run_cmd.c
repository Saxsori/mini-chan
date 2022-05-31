/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_run_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:29:54 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/31 11:24:59 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
! for now this is just working for only one cmd
! this part u should discuss with how it should work
!	with processes 
	// printf("2:%d\n", cmd->main->cmd_num);
*/
int	which_command(t_mini_cmd *cmd)
{
	if (!ft_strncmp(cmd->name, "cd", ft_strlen(cmd->name)))
		return (mini_cd(cmd));
	if (!ft_strncmp(cmd->name, "echo", ft_strlen(cmd->name)))
		return (mini_echo(cmd));
	if (!ft_strncmp(cmd->name, "pwd", ft_strlen(cmd->name)))
		return (mini_pwd(cmd));
	if (!ft_strncmp(cmd->name, "export", ft_strlen(cmd->name)))
		return (mini_export(cmd));
	if (!ft_strncmp(cmd->name, "unset", ft_strlen(cmd->name)))
		return (mini_unset(cmd));
	if (!ft_strncmp(cmd->name, "env", ft_strlen(cmd->name)))
		return (mini_env(cmd));
	if (!ft_strncmp(cmd->name, "exit", ft_strlen(cmd->name)))
		return (mini_exit(cmd));
	return (0);
}

/*
! this should be changed base on what boo decide for how the process should work
! and call this function
*/
int	run_cmd(t_shell_chan *main)
{
	if (main->cmd_num == 1)
		return (which_command(main->cmd_table));
	return (0);
}
