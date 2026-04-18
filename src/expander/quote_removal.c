/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:00:52 by asari             #+#    #+#             */
/*   Updated: 2026/04/17 17:43:14 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strip_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	char	quote;

	new_str = gc_malloc(sizeof(char) * (ft_strlen(str) + 1), GC_TEMP);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote != 0 && str[i] == quote)
			quote = 0;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	remove_quotes(t_token *token)
{
	char	*tmp;

	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			tmp = strip_quotes(token->value);
			token->value = tmp;
		}
		token = token->next;
	}
}
