/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_wrappers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:14:19 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:14:21 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*gc_strdup(const char *s1, t_gc_type type)
{
	char	*res;

	res = ft_strdup(s1);
	if (res)
		gc_add_node(res, type);
	return (res);
}

char	*gc_strjoin(char const *s1, char const *s2, t_gc_type type)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (res)
		gc_add_node(res, type);
	return (res);
}

char	*gc_substr(char const *s, unsigned int start, size_t len, t_gc_type type)
{
	char	*res;

	res = ft_substr(s, start, len);
	if (res)
		gc_add_node(res, type);
	return (res);
}

char	**gc_split(char const *s, char c, t_gc_type type)
{
	char	**res;
	int		i;

	res = ft_split(s, c);
	if (res)
	{
		gc_add_node(res, type);
		i = 0;
		while (res[i])
		{
			gc_add_node(res[i], type);
			i++;
		}
	}
	return (res);
}

char	*gc_itoa(int n, t_gc_type type)
{
	char	*res;

	res = ft_itoa(n);
	if (res)
		gc_add_node(res, type);
	return (res);
}
