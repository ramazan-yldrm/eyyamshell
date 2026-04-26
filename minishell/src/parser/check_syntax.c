/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:30:12 by asari             #+#    #+#             */
/*   Updated: 2026/04/26 17:30:13 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (1);
	if (token->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			2);
		get_set_status(1, 2);
		return (0);
	}
	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE
			&& (!tmp->next || tmp->next->type == TOKEN_PIPE))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
				2);
			get_set_status(1, 2);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
