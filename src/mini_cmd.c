/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:47:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/23 07:20:27 by aaljaber         ###   ########.fr       */
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
	// printf("here %d\n", cmd->tools.y_redir);
	if (!cmd->tools.y_redir)
		check_echo_opt(cmd);
	else if (cmd->tools.y_redir)
		get_echo_arg_redir(cmd);
	while (++i < cmd->tools.arg_num)
	{
		// if (is_extst(cmd->arguments[i]))
		// 	printf(BCYN"%d "BWHT, cmd->main->exit_status);
		// else
			printf("%s ", cmd->arguments[i]);
	}
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
	// int	i;

	// i = 0;
	if (cmd->option)
		pre_exit_arg(cmd);
	printf(" BOO exit cmd %d\n", cmd->tools.arg_num);
	if (cmd->tools.arg_num > 1)
	{
		printf(" too many args exit cmd %d %s\n", \
		cmd->tools.arg_num, cmd->arguments[0]);
		if (!ft_atoi(cmd->arguments[0]))
		{
			printf("exit\n");
			printf("mini-chan🌸$: exit: %s: numeric argument required\n", cmd->arguments[0]);
			exit(255);//todo
		}
		else
		{
			printf("exit\n");
			printf("mini-chan🌸$: exit: too many arguments\n");
			exit(1);
		}
	}
	else if (cmd->tools.arg_num == 0 || cmd->tools.arg_num == 1)
	{
		printf(" one exit cmd %d\n", cmd->tools.arg_num);
		exit(0);
	}
	return (0);
}
