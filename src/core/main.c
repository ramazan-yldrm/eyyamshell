#include "minishell.h"

int	g_signal = 0;

static void	process_input(char *input, t_env **env)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = lexer(input);
	if (!tokens)
		return ;
	expander(tokens, *env);
	remove_empty_tokens(&tokens);
	remove_quotes(tokens);
	cmd = parser(tokens);
	if (cmd)
		executer(cmd, env);
}

static void	run_tester(char *cmd_str, t_env **env)
{
	process_input(cmd_str, env);
	gc_free_type(GC_TEMP);
}

static void	handle_signal(void)
{
	if (g_signal == SIGINT)
	{
		get_set_status(1, 130);
		g_signal = 0;
	}
}

static void	interactive_loop(t_env **env)
{
	char	*input;

	while (1)
	{
		setup_signals();
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			cleanup_and_exit(get_set_status(0, 0));
		}
		handle_signal();
		gc_add_node(input, GC_TEMP);
		if (*input)
		{
			add_history(input);
			process_input(input, env);
		}
		gc_free_type(GC_TEMP);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;

	env_list = NULL;
	setup_signals();
	env_list = env_init(envp);
	env_check_missing(&env_list);
	if (argc == 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		run_tester(argv[2], &env_list);
		return (get_set_status(0, 0));
	}
	interactive_loop(&env_list);
	return (get_set_status(0, 0));
}
