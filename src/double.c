/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 00:37:42 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/28 18:31:04 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../mini_chan.h"

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
	temp->env = data;
	head = temp;
	// free(temp);
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
	temp->env = data;
	traversal = head;
	while (traversal->next != NULL)
		traversal = traversal->next;
	traversal->next = temp;
	temp->prev = traversal;
	// free (temp);
	// free (traversal);
	return (head);
}

t_mini_envar	*create_envar_list(t_mini_envar *head)
{
	head = creat_first_node(head, "path");
	head = add_node_at_end(head, "lala");
	head = add_node_at_end(head, "lala");
	head = add_node_at_end(head, "lala");
	head = add_node_at_end(head, "lala");
	return (head);
}

void	print_envar_list(t_mini_envar *head)
{
	t_mini_envar *print;
	
	print = head;
	while (print != NULL)
	{
		printf("%s\n", print->env);
		print = print->next;
	}
}

int main (int argc, char **argv, char **env)
{
	t_shell_chan main;
	int	i;
	
	(void) argc;
	(void) argv;	
	i = -1;
	while (env[++i])
	{
		printf("%s\n", env[i]);
	}
	main.head_envar = create_envar_list(main.head_envar);
	// print_envar_list(main.head_envar);
	return(0);
}
//    char *pathvar;
 
//    pathvar = getenv("PATH");
//    printf("pathvar=%s",pathvar);
