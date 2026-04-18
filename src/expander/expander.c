/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:06:12 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:06:36 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_single_node(t_token *token, t_env *env)
{
	int	i;
	int	in_sq;
	int	in_dq;

	if (!token || !token->value)
		return ;
	i = 0;
	in_sq = 0;
	in_dq = 0;
	while (token->value && token->value[i])
	{
		if (token->value[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (token->value[i] == '\"' && !in_sq)
			in_dq = !in_dq;
		else if (token->value[i] == '$' && !in_sq)
		{
			if (token->value[i + 1] != '?' && !ft_isalnum(token->value[i + 1])
				&& token->value[i + 1] != '_')
			{
				i++;
				continue ;
			}
			handle_expansion(token, &i, env);
			continue ;
		}
		i++;
	}
}

void	expander(t_token *token, t_env *env)
{
	while (token)
	{
		expand_single_node(token, env);
		token = token->next;
	}
}
