/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 04:27:25 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

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

void	change_pwd(t_mini_cmd *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	cmd->tools.envar = search_envar(cmd->main->head_envar, "PWD");
	if (cmd->tools.envar)
	{
		free(cmd->tools.envar->env_cont);
		if (cmd->main->d_rootpath)
			cmd->tools.envar->env_cont = ft_strjoin("/", pwd);
		else
			cmd->tools.envar->env_cont = ft_strdup(pwd);
	}
	cmd->tools.envar = NULL;
	free(pwd);
}

void	change_oldpwd(t_mini_cmd *cmd)
{
	t_mini_envar	*envar;
	char			*data;

	cmd->tools.envar = search_envar(cmd->main->head_envar, "OLDPWD");
	envar = search_envar(cmd->main->head_envar, "PWD");
	if (cmd->tools.envar)
	{
		free(cmd->tools.envar->env_cont);
		cmd->tools.envar->env_cont = ft_strdup(envar->env_cont);
		cmd->tools.envar->declared = 1;
	}
	else
	{
		data = ft_strjoin("OLDPWD=", envar->env_cont);
		add_node_at_end(cmd->main->head_envar, data, 'n');
	}
}

void	update_cd_envars(t_mini_cmd *cmd)
{
	cmd->tools.envar = search_envar(cmd->main->head_envar, "PWD");
	if (cmd->tools.envar->declared)
		change_oldpwd(cmd);
	else
	{
		cmd->tools.envar = search_envar(cmd->main->head_envar, "OLDPWD");
		if (cmd->main->f_pwd)
		{
			cmd->main->f_pwd = 0;
			if (!cmd->tools.envar->declared)
				cmd->tools.envar->declared = 1;
			free(cmd->tools.envar->env_cont);
			cmd->tools.envar->env_cont = malloc(sizeof(char));
			cmd->tools.envar->env_cont[0] = '\0';
		}
		else
			change_oldpwd(cmd);
	}
	change_pwd(cmd);
	cmd->tools.envar = NULL;
}
