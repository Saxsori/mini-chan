/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:47:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/27 20:18:06 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

// printf("%s\n", cmd->arguments[0]);
	// if (cmd->arguments[0] == NULL)
int	mini_cd(t_mini_cmd *cmd)
{
	if (chdir(cmd->arguments[0]) == -1)
	{
		printf(BRED"mini-chan🌸: cd: %s: No such file or directory\n", \
			cmd->arguments[0]);
		return (0);
	}
	return (1);
}

int	mini_echo(t_mini_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->tools.arg_num)
		printf("%s ", cmd->arguments[i]);
	if (!cmd->option)
		printf("\n");
	return (1);
}

int	mini_pwd(t_mini_cmd *cmd)
{
	cmd->tools.pwd = (char *)malloc(1024 * sizeof(char));
	cmd->tools.cwd_ret = getcwd(cmd->tools.pwd, 1024);
	if (cmd->tools.cwd_ret != NULL)
	{
		printf(BGRN"%s\n", cmd->tools.pwd);
		return (1);
	}
	else
	{
		printf(BRED"Error: %s\n", strerror(errno));
		return (0);
	}
}

int	mini_exit(t_mini_cmd *cmd)
{
	exit(ft_atoi(cmd->arguments[0]));
}
