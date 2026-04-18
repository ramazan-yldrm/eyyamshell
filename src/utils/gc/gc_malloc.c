/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:00:34 by asari             #+#    #+#             */
/*   Updated: 2026/04/15 16:42:06 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gc_malloc(size_t size, t_gc_type type)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		cleanup_and_exit(1, "GC: Malloc failed");
	gc_add_node(ptr, type);
	return (ptr);
}
