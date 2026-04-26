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

static void	handle_dollar_at(t_token *token, int *i, int in_dq, t_env *env)
{
	char	next;

	next = token->value[*i + 1];
	if (!in_dq && (next == '\'' || next == '\"'))
	{
		ft_memmove(&token->value[*i], &token->value[*i + 1],
			ft_strlen(&token->value[*i + 1]) + 1);
		return ;
	}
	if (next != '?' && !ft_isalnum(next) && next != '_')
	{
		(*i)++;
		return ;
	}
	handle_expansion(token, i, env);
}

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
	while (token->value[i])
	{
		if (token->value[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (token->value[i] == '\"' && !in_sq)
			in_dq = !in_dq;
		else if (token->value[i] == '$' && !in_sq)
		{
			handle_dollar_at(token, &i, in_dq, env);
			continue ;
		}
		i++;
	}
}

void	remove_empty_tokens(t_token **tokens)
{
	t_token	*curr;
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	curr = *tokens;
	while (curr)
	{
		next = curr->next;
		if (curr->type == TOKEN_WORD && curr->value[0] == '\0')
		{
			if (curr->prev)
				curr->prev->next = curr->next;
			else
				*tokens = curr->next;
			if (curr->next)
				curr->next->prev = curr->prev;
		}
		curr = next;
	}
}

void	expander(t_token *token, t_env *env)
{
	while (token)
	{
		if (token->prev && token->prev->type == TOKEN_HEREDOC)
		{
			token = token->next;
			continue ;
		}
		expand_single_node(token, env);
		token = token->next;
	}
}
