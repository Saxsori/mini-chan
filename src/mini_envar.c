/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_envar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:22:48 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/28 19:30:15 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
? the main function to create the list
? creating the first node and add the first env
? adding the other env in loop
	// print_envar_list(main->head_envar);
*/
void	create_envar_list(t_shell_chan *main, char **env)
{
	int	i;

	main->head_envar = creat_first_node(main->head_envar, env[0]);
	i = 0;
	while (env[++i])
		main->head_envar = add_node_at_end(main->head_envar, env[i]);
}

/*
head here is just a pointer that will point to the first node of the
 list so passing that pointer ..
? 1- malloc a temp pointer on the size of one node
? 2- passing null to the pointer of the prev and next pointer
?	since there it's the first node created
? 3- passing the pointer of temp to head so that head can point to the first 
?	node created which is the head of the list
? 4- return head to the head pointer in the main function
*/
t_mini_envar	*creat_first_node(t_mini_envar *head, char *data)
{
	t_mini_envar	*temp;

	temp = (t_mini_envar *)malloc(sizeof(t_mini_envar));
	temp->prev = NULL;
	temp->next = NULL;
	add_env_data(temp, data);
	head = temp;
	return (head);
}

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
	int		i;

	i = 1;
	split = ft_split(data, '=');
	temp->env_name = ft_strdup(split[0]);
	if (twstrlen(split) <= 2)
	{
		if (split[1] != NULL)
			temp->env_cont = ft_strdup(split[1]);
		else
			temp->env_cont = NULL;
	}
	if (twstrlen(split) > 2)
	{
		while (++i < twstrlen(split))
			temp->env_cont = ft_strjoin(temp->env_cont, split[i]);
	}
	sequared_free(split);
}

/*
-> to print the content of the list
? taking the pointer of the head into a temp pointer 
? if it was not NULL then moving form the next pointer of the head till 
? the end of the list and print the content
*/
void	print_envar_list(t_mini_envar *head)
{
	t_mini_envar	*print;

	print = head;
	while (print != NULL)
	{
		printf(BCYN"%s=%s\n"BWHT, print->env_name, print->env_cont);
		print = print->next;
	}
}
