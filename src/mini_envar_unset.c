/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_envar_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:06:03 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/28 23:19:16 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
to delete the first node
? 1- make the head points to the second node (next pointer)
? 2- free the prev node which is the first one
? 3- then set NULL on prev pointer to make the current the first one
*/
t_mini_envar	*del_first_envar(t_mini_envar *head)
{
	head = head->next;
	free(head->prev);
	head->prev = NULL;
	return (head);
}

/*
to delete the last node
? 1- need to look for the last node so set the traversal
?	into the head to move from the beginnig
? 2- when the next is NULL stop moving and store the prev pointer
?	in temp (the one b4 the last)
? 3- set the next pointer in temp to NULL so it's the last one
? 4- free the traversal which is the last node
*/
t_mini_envar	*del_last_envar(t_mini_envar *head)
{
	t_mini_envar	*temp;
	t_mini_envar	*traversal;

	traversal = head;
	while (traversal->next != NULL)
		traversal = traversal->next;
	temp = traversal->prev;
	temp->next = NULL;
	free(traversal);
	return (head);
}

/*
to delete the middle node
	we have the pointer of the node that we need to delete
? 1- set a temp which equal to the node b4 envar
? 2- since the mid one (envar) will be deleted so the next node of 
?	envar should be the next of the prev (temp)
? 3- and the prev of the next one should be temp
*  | -> from  || -> to
*          ----------------------------------
*          |                                ||
*    --------           --------           --------
*	| P || N |         | P || N |         | P || N |
*    --------           --------           --------
*    temp  ||            envar              |      
*	        --------------------------------
*/
void	del_mid_envar(t_mini_envar *envar)
{
	t_mini_envar	*temp;

	temp = envar->prev;
	temp->next = envar->next;
	envar->next->prev = temp;
	free (envar);
	envar = NULL;
}
