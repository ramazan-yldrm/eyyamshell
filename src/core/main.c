#include "minishell.h"
#include "libft.h"

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
			remove_empty_tokens(&token);
			remove_quotes(token);
			cmd = parser(token);
			if (cmd)
				executer(cmd, &env_list);
		}
		gc_free_type(GC_TEMP);
		return (get_set_status(0, 0));
	}

	// 🔁 INTERACTIVE MOD
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			cleanup_and_exit(get_set_status(0, 0));
		}
		gc_add_node(input, GC_TEMP);
		if (*input)
			add_history(input);
		token = lexer(input);
		if (token)
		{
			expander(token, env_list);
			remove_empty_tokens(&token);
			remove_quotes(token);
			cmd = parser(token);
			if (cmd)
				executer(cmd, &env_list);
		}
		gc_free_type(GC_TEMP);
	}
	return (0);
}