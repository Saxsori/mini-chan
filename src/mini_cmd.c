/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:47:29 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"
#include <stdlib.h>

int	mini_cd(t_mini_cmd *cmd)
{
	if (!cmd->arguments)
		return (cd_home(cmd));
	else if (cmd->tools.arg_num > 1)
	{
		errmsg(cmd->name, TMA);
		return (1);
	}
	else
	{
		if (change_dir(cmd))
			return (1);
	}
	return (0);
}

/*
	// else if (cmd->tools.y_redir)
	// 	get_echo_arg_redir(cmd);
		printf("%s", cmd->arguments[i]);
*/
int	mini_echo(t_mini_cmd *cmd)
{
	int	i;

	i = -1;
	if (!cmd->tools.y_redir)
		check_echo_opt(cmd);
	while (++i < cmd->tools.arg_num - 1)
	{
		ft_putstr_fd(cmd->arguments[i], 1);
		ft_putchar_fd(' ', 1);
	}
	if (cmd->tools.arg_num)
		ft_putstr_fd(cmd->arguments[i], 1);
	if (!cmd->option)
		ft_putchar_fd('\n', 1);
	return (0);
}

/*
		// printf(BCYN"%s\n"BWHT, cmd->tools.envar->env_cont);
*/
int	mini_pwd(t_mini_cmd *cmd)
{
	cmd->tools.envar = search_envar(cmd->main->head_envar, "PWD");
	if (cmd->tools.envar)
	{
		ft_putstr_fd(cmd->tools.envar->env_cont, 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		cmd->tools.cwd_ret = getcwd(NULL, 1024);
		ft_putstr_fd(cmd->tools.cwd_ret, 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}

void	exit_more_arg(t_mini_cmd *cmd, int check_ret)
{
	char	*line;

	if (check_ret == 1)
	{
		line = ft_strjoin(cmd->arguments[0], \
		": numeric argument required\n");
		exit_msg(cmd->main, "255", &line);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		errmsg("exit", TMA);
		cmd->main->exit_status = 1;
	}
}

/*
! chmge the exiy=t status for no argument to g_status 
*/
int	mini_exit(t_mini_cmd *cmd)
{
	int		check_ret;
	char	*line;

	check_ret = -1;
	if (cmd->option)
		pre_exit_arg(cmd);
	if (cmd->tools.arg_num > 0)
		check_ret = check_first_arg(cmd);
	if (cmd->tools.arg_num == 0)
		ft_exit(cmd->main, g_status);
	check_ret = check_first_arg(cmd);
	if (cmd->tools.arg_num > 1)
		exit_more_arg(cmd, check_ret);
	else if ((cmd->tools.arg_num == 0 || cmd->tools.arg_num == 1) \
	&& check_ret == 0)
		exit_msg(cmd->main, cmd->arguments[0], NULL);
	else if ((cmd->tools.arg_num == 1) && !check_first_arg(cmd))
		exit_msg(cmd->main, cmd->arguments[0], NULL);
	else if (check_ret == 1 && cmd->tools.arg_num == 1)
	{
		line = ft_strjoin(cmd->arguments[0], ": numeric argument required\n");
		exit_msg(cmd->main, "255", &line);
	}
	return (cmd->main->exit_status);
}
