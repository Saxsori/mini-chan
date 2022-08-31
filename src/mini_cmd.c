/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:47:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/31 02:13:43 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"
#include <stdlib.h>

int	mini_cd(t_mini_cmd *cmd)
{
	int				ret;
	char			*pwd;
	char			*temp;
	char			*rett;

	pwd = (char *)malloc(1024 * sizeof(char));
	getcwd(pwd, 1024);
	if (!cmd->arguments)
		cd_home(cmd, pwd);
	else
	{
		ret = chdir(cmd->arguments[0]);
		printf("ret %d\n", ret);
		if (ret == -1)
		{
			printf(BRED"mini-chan🌸: cd: %s: %s\n"BWHT, \
				cmd->arguments[0], strerror(errno));
			free (pwd);
			return (1);
		}
		else
		{
			temp = (char *)malloc(1024 * sizeof(char));
			rett = getcwd(temp, 1024);
			printf("cwd %s\n", rett);
			if (!temp)
			{
				printf ("lll\n");
				free(temp);
				cmd->tools.envar = search_envar(cmd->main->head_envar, "PWD");
				temp = ft_strjoin(cmd->tools.envar->env_cont, "/..");
				free (cmd->tools.envar->env_cont);
				cmd->tools.envar->env_cont = ft_strdup(temp);
				free (temp);
			}
			else
			{
				check_root(cmd);
				change_oldpwd(cmd, pwd);
				change_pwd(cmd, pwd);
			}
		}
	}
	free (pwd);
	return (0);
}

int	mini_echo(t_mini_cmd *cmd)
{
	int	i;

	i = -1;
	if (!cmd->tools.y_redir)
		check_echo_opt(cmd);
	else if (cmd->tools.y_redir)
		get_echo_arg_redir(cmd);
	while (++i < cmd->tools.arg_num)
		printf("%s ", cmd->arguments[i]);
	if (!cmd->option)
		printf("\n");
	return (0);
}

int	mini_pwd(t_mini_cmd *cmd)
{
	cmd->tools.envar = search_envar(cmd->main->head_envar, "PWD");
	// cmd->tools.pwd = (char *)malloc(1024 * sizeof(char));
	// cmd->tools.cwd_ret = getcwd(cmd->tools.pwd, 1024);
	// printf("cwd %s\n", cmd->tools.cwd_ret);
	// if (cmd->tools.cwd_ret != NULL)
	// {
	// 	if (cmd->main->d_rootpath == 1)
	// 		printf(BCYN"/%s\n"BWHT, cmd->tools.pwd);
	// 	else
	// 		printf(BCYN"%s\n"BWHT, cmd->tools.pwd);
	// }
	printf(BCYN"%s\n"BWHT, cmd->tools.envar->env_cont);
	return (0);
}


int	mini_exit(t_mini_cmd *cmd)
{
	int		check_ret;
	char	*line;

	check_ret = -1;
	if (cmd->option)
		pre_exit_arg(cmd);
	if (cmd->tools.arg_num > 0)
		check_ret = check_first_arg(cmd);
	if (cmd->tools.arg_num == 0 )
		exit(0);
	check_ret = check_first_arg(cmd);
	if (cmd->tools.arg_num > 1)
	{
		if (check_ret == 1)
		{
			line = ft_strjoin(cmd->arguments[0], ": numeric argument required\n");
			exit_msg(cmd->main, "255", &line);
			// printf("exit\n");
			// printf("1 mini-chan🌸$: exit: %s: numeric argument required\n", 
			// cmd->arguments[0]);
			// exit(255);
		}
		else
		{
			printf("exit\n");
			printf("mini-chan🌸$: exit: too many arguments\n");
		}
	}
	else if ((cmd->tools.arg_num == 0 || cmd->tools.arg_num == 1) \
	&& check_ret == 0)
	{
		exit_msg(cmd->main, cmd->arguments[0], NULL);
		// printf("exit\n");
		// exit(ft_atoi(cmd->arguments[0]));
	}
	else if ((cmd->tools.arg_num == 1) && !check_first_arg(cmd))
	{
		exit_msg(cmd->main, cmd->arguments[0], NULL);
		// printf("exit\n");
		// exit(ft_atoi(cmd->arguments[0]));
	}
	else if (check_ret == 1 && cmd->tools.arg_num == 1)
	{
		line = ft_strjoin(cmd->arguments[0], ": numeric argument required\n");
		exit_msg(cmd->main, "255", &line);
		// printf("exit\n");
		// printf("2 mini-chan🌸$: exit: %s: numeric argument required\n", 
		// cmd->arguments[0]);
		// exit(255);
	}
	return (0);
}

void	exit_msg(t_shell_chan *main, char *status, char **msg)
{
	printf("exit\n");
	if (msg)
	{
		printf("mini-chan🌸$: %s\n",*msg);
		free_ptr((void **)msg);
	}
	ft_exit(main, ft_atoi(status));
}