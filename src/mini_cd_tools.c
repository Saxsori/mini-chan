/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:14 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/31 01:55:12 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	is_doubslash(char *line)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '/')
			k++;
	}
	return (k);
}

void	check_root(t_mini_cmd *cmd)
{
	if (is_doubslash(cmd->arguments[0]) == 2)
		cmd->main->d_rootpath = 1;
	else if (is_doubslash(cmd->arguments[0]) != 2 \
			&& is_doubslash(cmd->arguments[0]) != 0)
		cmd->main->d_rootpath = 0;
}

void	change_pwd(t_mini_cmd *cmd, char *pwd)
{
	getcwd(pwd, 1024);
	cmd->tools.envar = search_envar(cmd->main->head_envar, "PWD");
	if (cmd->tools.envar)
	{
		free(cmd->tools.envar->env_cont);
		if (cmd->main->d_rootpath)
			cmd->tools.envar->env_cont = ft_strjoin("/", pwd);
		else
			cmd->tools.envar->env_cont = ft_strdup(pwd);
	}
}

void	change_oldpwd(t_mini_cmd *cmd, char *pwd)
{
	char	*data;

	if (check_is_name_there(cmd->main, "OLDPWD"))
	{
		cmd->tools.envar = search_envar(cmd->main->head_envar, "OLDPWD");
		free(cmd->tools.envar->env_cont);
		cmd->tools.envar->env_cont = ft_strdup(pwd);
		cmd->tools.envar->declared = 1;
	}
	else
	{
		data = ft_strjoin("OLDPWD=", pwd);
		add_node_at_end(cmd->main->head_envar, data, 'n');
	}
}

void	cd_home(t_mini_cmd *cmd, char *pwd)
{
	cmd->tools.envar = search_envar(cmd->main->head_envar, "HOME");
	chdir(cmd->tools.envar->env_cont);
	change_oldpwd(cmd, pwd);
	change_pwd(cmd, pwd);
}
