/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:15:59 by asari             #+#    #+#             */
/*   Updated: 2026/01/08 15:44:56 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *input)
{
	t_token	*token;
	t_token	*new_token;
	char	*curr;

	token = NULL;
	curr = input;
	while (*curr)
	{
		while (*curr && is_space(*curr))
			curr++;
		if (!*curr)
			break ;
		if (*curr == '|')
			new_token = handle_pipe(&curr);
		else if (*curr == '<' || *curr == '>')
			new_token = handle_redirect(&curr);
		else
			new_token = handle_word(&curr);
		if (!new_token)
			return (NULL);
		token_add_back(&token, new_token);
	}
	return (token);
}
