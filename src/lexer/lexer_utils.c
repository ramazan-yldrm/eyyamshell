/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:16:24 by asari             #+#    #+#             */
/*   Updated: 2026/01/08 15:44:52 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*token_new_node(char *value, t_token_type type)
{
	t_token	*new_token;

	if (!value)
		return (NULL);
	new_token = gc_malloc(sizeof(t_token), GC_TEMP);
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	token_add_back(t_token **token, t_token *new_token)
{
	t_token	*temp;

	if (!new_token)
		return ;
	new_token->next = NULL;
	if (!*token)
	{
		*token = new_token;
		new_token->prev = NULL;
		return ;
	}
	temp = *token;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
	new_token->prev = temp;
}
