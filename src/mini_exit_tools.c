/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:22:12 by balnahdi          #+#    #+#             */
/*   Updated: 2022/09/15 00:23:08 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
	1 while check if all first arg contain 0s (exit 000000000)
		if all 0s return 0
	2 while check if all numbers using atoi (one case wont be handeld)
*/

int	ft_scan_num(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_long(char *str)
{
	int	len;

	len = ft_strlen(str);
	if ((str[0] == '-' || str[0] == '+') && ft_strlen(str) == 19)
	{
		if (str[len -1] > '0')
			return (1);
		else
			return (0);
	}
	if ((str[0] != '-' || str[0] != '+') && ft_strlen(str) == 18)
	{
		if (str[len -1] > '0')
			return (1);
		else
			return (0);
	}	
	if (ft_strlen(str) < 18)
		return (0);
	return (1);
}

int	check_first_arg(t_mini_cmd *cmd)
{
	int	len;
	int	i;

	if (!cmd->arguments[0])
		return (-1);
	i = 0;
	len = ft_strlen(cmd->arguments[0]);
	if (!ft_strncmp(cmd->arguments[0], "-9223372036854775808", \
	ft_strlen(cmd->arguments[0])))
		return (0);
	if (!ft_strncmp(cmd->arguments[0], "-9223372036854775809", \
	ft_strlen(cmd->arguments[0])))
		return (1);
	if (!ft_strncmp(cmd->arguments[0], "9223372036854775809", \
	ft_strlen(cmd->arguments[0])))
		return (1);
	if (!ft_strncmp(cmd->arguments[0], "9223372036854775808", \
	ft_strlen(cmd->arguments[0])))
		return (1);
	if (cmd->arguments[0][i] == '+' || cmd->arguments[0][i] == '-' )
		i++;
	while (cmd->arguments[0][i] == '0')
		i++;
	if (i == len)
		return (0);
	if ((ft_atoi(cmd->arguments[0]) && ft_scan_num(cmd->arguments[0])) \
	|| (ft_scan_num(cmd->arguments[0]) && check_long(cmd->arguments[0])))
		return (0);
	return (1);
}
