/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_add_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:54:26 by asari             #+#    #+#             */
/*   Updated: 2026/04/18 21:14:06 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gc_add_node(void *value, t_gc_type type)
{
	t_gc	**collector;
	t_gc	*new_node;

	if (!value)
		return ;
	collector = get_collector();
	new_node = malloc(sizeof(t_gc));
	if (!new_node)
	{
		free(value);
		perror_and_sstatus("fatal", NULL, ERR_MALLOC, EXIT_FAILURE);
		cleanup_and_exit(1);
	}
	new_node->value = value;
	new_node->type = type;
	new_node->next = *collector;
	new_node->prev = NULL;
	if (*collector)
		(*collector)->prev = new_node;
	(*collector) = new_node;
}
