/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:07:04 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:07:46 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_expansion(t_token *token, int *i, t_env *env)
{
	int		j;
	char	*key;
	char	*value;
	char	*new_text;
	char	*rep;

	j = *i + 1;
	if (token->value[j] == '?')
		j++;
	else
	{
		while (token->value[j] && (ft_isalnum(token->value[j])
				|| token->value[j] == '_'))
			j++;
	}
	key = gc_substr(token->value, *i + 1, j - *i - 1, GC_TEMP);
	value = env_get_value(key, env);
	rep = ft_ternary_str(value, "");
	new_text = replace_str(token->value, rep, *i, j - 1);
	token->value = new_text;
	*i = *i + ft_strlen(rep);
}
