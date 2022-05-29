/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_envar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:22:48 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/28 23:02:20 by aaljaber         ###   ########.fr       */
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
