#include "minishell.h"
#include "libft.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*token;
	t_cmd	*cmd;
	t_env	*env_list;

	setup_signals();
	env_list = env_init(envp);
	env_check_missing(&env_list);

	// 🔥 BURASI: -c desteği
	if (argc == 3 && strcmp(argv[1], "-c") == 0)
	{
		input = argv[2];
		token = lexer(input);
		if (token)
		{
			expander(token, env_list);
			remove_quotes(token);
			cmd = parser(token);
			if (cmd)
				executor(cmd, &env_list);
		}
		gc_free_type(GC_TEMP);
		return (g_exit_status);
	}

	// 🔁 INTERACTIVE MOD
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
			remove_quotes(token);
			cmd = parser(token);
			if (cmd)
				executor(cmd, &env_list);
		}
		gc_free_type(GC_TEMP);
	}
	return (0);
}