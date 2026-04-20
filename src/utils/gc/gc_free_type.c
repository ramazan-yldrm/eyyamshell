/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:00:30 by asari             #+#    #+#             */
/*   Updated: 2026/04/18 21:15:59 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gc_free_type(t_gc_type type)
{
	t_gc	**collector;
	t_gc	*next_node;
	t_gc	*curr;

	collector = get_collector();
	curr = *collector;
	while (curr)
	{
		next_node = curr->next;
		if (curr->type == type)
		{
			if (curr->prev)
				curr->prev->next = curr->next;
			if (curr->next)
				curr->next->prev = curr->prev;
			if (curr == (*collector))
				(*collector) = curr->next;
			free(curr->value);
			free(curr);
		}
		curr = next_node;
	}
}
