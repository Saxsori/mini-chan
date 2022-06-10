/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_envar_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:02:00 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/09 22:00:16 by aaljaber         ###   ########.fr       */
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
t_mini_envar	*add_node_at_end(t_mini_envar *head, char *data)
{
	t_mini_envar	*temp;
	t_mini_envar	*traversal;

	temp = (t_mini_envar *)malloc(sizeof(t_mini_envar));
	temp->prev = NULL;
	temp->next = NULL;
	add_env_data(temp, data);
	traversal = head;
	while (traversal->next != NULL)
		traversal = traversal->next;
	traversal->next = temp;
	temp->prev = traversal;
	return (head);
}

/*
? env_name is pointer here and you cant pass any value 
? to a pointer that u didn't malloc
*/
void	add_env_data(t_mini_envar *temp, char *data)
{
	char	**split;

	split = ft_split(data, '=');
	temp->env_name = ft_strdup(split[0]);
	squaredstr_free(split);
	if (ft_strchr(data, '=', 2) != NULL)
		temp->env_cont = ft_strchr(data, '=', 2);
	else
	{
		temp->env_cont = (char *)malloc(sizeof(char));
		temp->env_cont[0] = '\0';
	}
}
