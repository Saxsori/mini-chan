/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:47:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/23 17:54:23 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"
#include <stdlib.h>

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
/*
	1 while check if all first arg contain 0s (exit 000000000)
		if all 0s return 0
	2 while check if all numbers using atoi (one case wont be handeld)
*/
int check_first_arg(t_mini_cmd *cmd)
{
	int i = 0;
	int non_num = 1;
	if(!cmd->arguments[0])
		return -1;
	int len = ft_strlen(cmd->arguments[0]);
	while(cmd->arguments[0][i] == '0')
		i++;
	if (i == len && non_num == 1)
		return (0);
	if(ft_atoi(cmd->arguments[0]))
	{
		printf("len %d i %d atoi ret %d\n",len,i,ft_atoi(cmd->arguments[0]));
		return (0);
	}
	printf("len %d i %d\n",len,i);
	return (1);
}

int	mini_exit(t_mini_cmd *cmd)
{
	int check_ret = 1; 
	if (cmd->option)
		pre_exit_arg(cmd);
	check_ret = check_first_arg(cmd);
	printf(" BOO exit cmd %d  exit arg %s .. check_ret %d\n", cmd->tools.arg_num,cmd->arguments[0],check_first_arg(cmd));
	if (cmd->tools.arg_num > 1)
	{
		printf(" too many args exit cmd %d %s\n", \
		cmd->tools.arg_num, cmd->arguments[0]);
		printf("return atoi = %d to %s\n",ft_atoi(cmd->arguments[0]),cmd->arguments[0]);
		// if (non_num == 0)
		// {
		// 	printf("exit\n");
		// 	printf("mini-chan🌸$: exit: %s: numeric argument required\n", cmd->arguments[0]);
		// 	exit(255);//todo
		// }
		// else if(non_num == 1)
		// {
		// 	printf("exit\n");
		// 	printf("mini-chan🌸$: exit: too many arguments\n");
		// 	// exit(1);
		// }
	}
	else if ((cmd->tools.arg_num == 0 || cmd->tools.arg_num == 1) && !check_first_arg(cmd))
	{
		printf(" one exit cmd %d %d .. atoi ret %d\n", cmd->tools.arg_num, check_first_arg(cmd),ft_atoi(cmd->arguments[0]));
		exit(ft_atoi(cmd->arguments[0]));
	}
	else if (check_first_arg(cmd) && cmd->tools.arg_num == 1)
	{
		printf("exit\n");
		printf("mini-chan🌸$: exit: %s: numeric argument required\n", cmd->arguments[0]);
		exit(255);
	}
	return (0);
}
