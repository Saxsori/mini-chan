/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:47:01 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/02 10:35:17 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

// void	check_echo_opt(t_mini_cmd *cmd)
// {
// 	int	i;

// 	i = -1;
// 	if (cmd->option)
// 	{
// 		if (is_echo_opt(cmd->option, '1', 0))
// 		{
// 			cmd->tools.y_op = 1;
// 			if (is_echo_opt(cmd->option, 'i', cmd->tools.opt_num) != -1)
// 			{
// 				i = is_echo_opt(cmd->option, 'i', cmd->tools.opt_num) - 1;
// 				while (++i < cmd->tools.opt_num - 1)
// 					printf(BCYN"%s "BWHT, cmd->option[i]);
// 			}
// 		}
// 		else
// 			cmd->tools.y_op = 0;
// 	}
// }

// int	is_echo_opt(char **opt, char which, int len)
// {
// 	int	i;

// 	i = 0;
// 	if (which == '1')
// 	{
// 		if (!ft_strncmp(opt[0], "-n", ft_strlen(opt[0])))
// 		{
// 			printf("1 yes\n");
// 			return (1);
// 		}
// 		printf("%s\n", opt[0]);
// 		printf("1 no\n");
// 		return (0);
// 	}
// 	if (which == 'i')
// 	{
// 		while (++i < len)
// 		{
// 			if (ft_strncmp(opt[i], "-n", ft_strlen(opt[i])))
// 			{
// 				printf("i no\n");
// 				return (i);
// 			}
// 		}
// 		printf("i yes\n");
// 		return (-1);
// 	}
// 	return (-1);
// }

int	is_echo_opt(char *line)
{
	int	i;

	i = 0;
	if (line[1] == '\0')
		return (0);
	while (++i < ft_strlen(line))
	{
		if (line[i] != 'n')
			return (0);
	}
	return (1);
}

void	handle_one_case(t_mini_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->tools.i_arg == 0)
	{
		while (++i < cmd->tools.opt_num)
			free(cmd->option[i]);
		free(cmd->option);
		cmd->option = NULL;
	}
}

/*
	// printf ("opt - index %d\n", cmd->tools.new_arg);
	// printf ("arg_num + new_arg %d\n", cmd->tools.new_arg_size);
*/
char	**new_arg(t_mini_cmd *cmd)
{
	int		i;
	int		k;
	char	**new_arg;

	cmd->tools.new_arg = cmd->tools.opt_num - cmd->tools.i_arg;
	cmd->tools.new_arg_size = cmd->tools.new_arg + cmd->tools.arg_num;
	new_arg = (char **)malloc(sizeof(char *) * (cmd->tools.new_arg_size + 1));
	new_arg[cmd->tools.new_arg_size] = NULL;
	i = -1;
	k = cmd->tools.i_arg;
	while (++i < cmd->tools.new_arg)
		new_arg[i] = ft_strdup(cmd->option[k++]);
	if (cmd->tools.arg_num)
	{
		k = -1;
		while (++k < cmd->tools.arg_num)
			new_arg[i++] = ft_strdup(cmd->arguments[k]);
		k = -1;
		while (++k < cmd->tools.arg_num)
			free(cmd->arguments[k]);
		free(cmd->arguments);
		cmd->arguments = NULL;
	}
	handle_one_case(cmd);
	return (new_arg);
}

/*

	// printf ("index %d\n", cmd->tools.i_arg);
	// i = -1;
	// while (++i < cmd->tools.arg_num)
	// 	printf("-> (%s)\n", cmd->arguments[i]);
*/
void	check_echo_opt(t_mini_cmd *cmd)
{
	int	i;

	// i = -1;
	cmd->tools.i_arg = -1;
	if (cmd->option)
	{
		// while (++i < cmd->tools.opt_num)
			// printf ("%s\n", cmd->option[i]);
		i = -1;
		while (++i < cmd->tools.opt_num)
		{
			if (!is_echo_opt(cmd->option[i]))
			{
				cmd->tools.i_arg = i;
				break ;
			}
		}
	}
	if (cmd->tools.i_arg != -1)
	{
		cmd->arguments = new_arg(cmd);
		cmd->tools.arg_num = cmd->tools.new_arg_size;
	}
}
