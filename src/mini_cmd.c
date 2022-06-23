/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:47:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/23 18:27:56 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

// printf("%s\n", cmd->arguments[0]);
	// if (cmd->arguments[0] == NULL)
int	mini_cd(t_mini_cmd *cmd)
{
	if (!cmd->arguments)
	{
		cmd->tools.envar = search_envar(cmd->main->head_envar, "HOME");
		chdir(cmd->tools.envar->env_cont);
	}
	else
	{
		if (chdir(cmd->arguments[0]) == -1)
		{
			printf(BRED"mini-chan🌸: cd: %s: %s\n"BWHT, \
				cmd->arguments[0], strerror(errno));
			return (0);
		}
		if (is_doubslash(cmd->arguments[0]) == 2)
			cmd->main->d_rootpath = 1;
		else if (is_doubslash(cmd->arguments[0]) != 2 \
				&& is_doubslash(cmd->arguments[0]) != 0)
			cmd->main->d_rootpath = 0;
	}
	return (1);
}

int	mini_echo(t_mini_cmd *cmd)
{
	int	i;

	i = -1;
	check_echo_opt(cmd);
	while (++i < cmd->tools.arg_num)
	{
		if (is_extst(cmd->arguments[i]))
			printf(BCYN"%d "BWHT, cmd->main->exit_status);
		else
			printf(BCYN"(%s) "BWHT, cmd->arguments[i]);
	}
	if (!cmd->option)
		printf("\n"BWHT);
	return (1);
}

int	mini_pwd(t_mini_cmd *cmd)
{
	cmd->tools.pwd = (char *)malloc(1024 * sizeof(char));
	cmd->tools.cwd_ret = getcwd(cmd->tools.pwd, 1024);
	if (cmd->tools.cwd_ret != NULL)
	{
		if (cmd->main->d_rootpath == 1)
			printf(BCYN"/%s\n"BWHT, cmd->tools.pwd);
		else
			printf(BCYN"%s\n"BWHT, cmd->tools.pwd);
		return (1);
	}
	else
	{
		printf(BRED"Error: %s\n"BWHT, strerror(errno));
		return (0);
	}
}

int	mini_exit(t_mini_cmd *cmd)
{
	if (!cmd->arguments)
	{
		printf(BCYN"exit\n"BWHT);
		exit(0);
	}
	else
	{
		printf(BCYN"exit\n"BWHT);
		exit(ft_atoi(cmd->arguments[0]));
	}
}
