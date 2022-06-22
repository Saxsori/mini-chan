/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_envar_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:02:00 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/22 16:58:31 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
here is the way to add a node to the end of an existed list 
 	and in order to do that u need to :
? 1- create a new node (temp) that u want to add
? 2- pass NULL to the prev and next pointers of the new node (temp)
? 3- pass the data to the new node (temp)
? 4- set the traversal var to the value of the head 
?	so it can start moving from the beginning of the list till 
?	it reach the NULL
? 5- moving from the next pointer of the head to the other nodes
?	till the next node is NULL which is the end of the list (travesral)
? 6- so the next pointer of the last node (travesral) instead of NULL it should
?	be the pointer of the new node added (temp)
? 7- and the prev pointer of the new node (temp) should be the pointer 
?	of the last pointer (travesral)
? 8- return the new head after making the change into the list
*/
t_mini_envar	*add_node_at_end(t_mini_envar *head, char *data, char op)
{
	t_mini_envar	*temp;
	t_mini_envar	*traversal;

	temp = (t_mini_envar *)malloc(sizeof(t_mini_envar));
	temp->prev = NULL;
	temp->next = NULL;
	add_env_data(temp, data);
	envar_mode(temp, op);
	traversal = head;
	while (traversal->next != NULL)
		traversal = traversal->next;
	traversal->next = temp;
	temp->prev = traversal;
	return (head);
}

/*
? hidden means it won't show when you do env and you can't modify it with export
? declared means it does have a value which it can be shown by env 
? but if it wasn't declared it won't be shown by env only by export
*/
void	envar_mode(t_mini_envar *temp, char op)
{
	if (op == 'n')
		temp->declared = 1;
	else if (op == 'x')
		temp->declared = 0;
}

/*
? env_name is pointer here and you cant pass any value 
? to a pointer that u didn't malloc
* n -> it's not hidden and declared so it will be normal splitted by thr first =
* x -> it's not hidden and not declared which it won't have a value so no splitting
* h -> it's hidden and not declared these value should be one by one init
*/
void	add_env_data(t_mini_envar *temp, char *data)
{
	char	**split;

	split = ft_split(data, '=');
	temp->env_name = ft_strdup(split[0]);
	squaredstr_free(split);
	if (!ft_strncmp(temp->env_name, "SHLVL", ft_strlen(temp->env_name)))
		temp->env_cont = ft_itoa(1);
	else if (ft_strchr(data, '=', 2) != NULL)
		temp->env_cont = ft_strchr(data, '=', 2);
	else
	{
		temp->env_cont = (char *)malloc(sizeof(char));
		temp->env_cont[0] = '\0';
	}
}

int	do_export(t_mini_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->tools.arg_num)
	{
		if (isvalid_name(cmd->arguments[i]))
		{
			if (is_equal(cmd->arguments[i]))
			{
				if (check_is_name_there(cmd->main, cmd->arguments[i]))
					replace_envar(cmd, i);
				else
					add_node_at_end(cmd->main->head_envar, cmd->arguments[i], 'n');
			}
			else if (!check_is_name_there(cmd->main, cmd->arguments[i]))
				add_node_at_end(cmd->main->head_envar, cmd->arguments[i], 'x');
		}
		else
		{
			printf(BRED"%d export: not a valid identifier\n", i);
			return (0);
		}
	}
	return (1);
}
