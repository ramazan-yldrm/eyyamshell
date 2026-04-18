/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:14:07 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:14:09 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gc_free_all(void)
{
	t_gc	**collector;
	t_gc	*curr;
	t_gc	*tmp;

	collector = get_collector();
	if (!collector || !*collector)
		return ;
	curr = *collector;
	while (curr)
	{
		tmp = curr->next;
		if (curr->value)
		{
			free(curr->value);
			curr->value = NULL;
		}
		free(curr);
		curr = tmp;
	}
	*collector = NULL;
}
