/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:14:08 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/11 11:12:10 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
? checking if this command is one of the commands that we will recode
! CHECK WITH BOO if this needs edition depending on the other builtin commands
*/
int	is_command(char *cmd_name)
{
	if (cmd_name)
	{
		if (!ft_strncmp(cmd_name, "cd", ft_strlen(cmd_name)))
			return (1);
		if (!ft_strncmp(cmd_name, "echo", ft_strlen(cmd_name)))
			return (1);
		if (!ft_strncmp(cmd_name, "pwd", ft_strlen(cmd_name)))
			return (1);
		if (!ft_strncmp(cmd_name, "export", ft_strlen(cmd_name)))
			return (1);
		if (!ft_strncmp(cmd_name, "unset", ft_strlen(cmd_name)))
			return (1);
		if (!ft_strncmp(cmd_name, "env", ft_strlen(cmd_name)))
			return (1);
		if (!ft_strncmp(cmd_name, "exit", ft_strlen(cmd_name)))
			return (1);
		if (!ft_strncmp(cmd_name, "mini-chan🌸", ft_strlen(cmd_name)))
			return (1);
	}
	return (0);
}
