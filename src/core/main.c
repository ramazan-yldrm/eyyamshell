/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 08:56:35 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/20 08:56:35 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*token;
	t_cmd	*cmd;
	t_env	*env_list;

	(void)argc;
	(void)argv;
	setup_signals();
	env_list = env_init(envp);
	env_check_missing(&env_list);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			cleanup_and_exit(g_exit_status, NULL);
		}
		gc_add_node(input, GC_TEMP);
		if (*input)
			add_history(input);
		token = lexer(input);
		if (token)
		{
			expander(token, env_list);
			remove_empty_tokens(&token);
			if (!token)
			{
				gc_free_type(GC_TEMP);
				continue ;
			}
			remove_quotes(token);
			cmd = parser(token);
			if (cmd)
				executor(cmd, &env_list);
		}
		gc_free_type(GC_TEMP);
	}
	return (0);
}
