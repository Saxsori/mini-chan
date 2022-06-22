/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:14:08 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/21 17:47:45 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	cmd_strncmp(const char *s1, const char *s2, int n)
{
	int				i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (ft_strlen(s1) > ft_strlen(s2))
		n = ft_strlen(s1);
	else
		n = ft_strlen(s2);
	i = 0;
	while (i < n && (p1[i] != '\0' || p2[i] != '\0'))
	{
		if (p1[i] != p2[i])
		{
			if (p1[i] - p2[i] != 32 || p1[i] - p2[i] != -32)
				return (p1[i] - p2[i]);
		}
		i++;
	}
	return (0);
}

/*
? checking if this command is one of the commands that we will recode
! CHECK WITH BOO if this needs edition depending on the other builtin commands
*/
int	is_command(char *cmd_name)
{
	if (cmd_name)
	{
		if (!cmd_strncmp(cmd_name, "cd", ft_strlen(cmd_name)))
			return (1);
		if (!cmd_strncmp(cmd_name, "echo", ft_strlen(cmd_name)))
			return (1);
		if (!cmd_strncmp(cmd_name, "pwd", ft_strlen(cmd_name)))
			return (1);
		if (!cmd_strncmp(cmd_name, "export", ft_strlen(cmd_name)))
			return (1);
		if (!cmd_strncmp(cmd_name, "unset", ft_strlen(cmd_name)))
			return (1);
		if (!cmd_strncmp(cmd_name, "env", ft_strlen(cmd_name)))
			return (1);
		if (!cmd_strncmp(cmd_name, "exit", ft_strlen(cmd_name)))
			return (1);
		if (!ft_strncmp(cmd_name, "mini-chan🌸", ft_strlen(cmd_name)))
			return (1);
	}
	return (0);
}
