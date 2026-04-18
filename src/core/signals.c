#include "../inc/minishell.h"
#include <signal.h>

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
void	setup_child_signals(void)
{
	struct sigaction	sa_dfl;

	sa_dfl.sa_handler = SIG_DFL;
	sigemptyset(&sa_dfl.sa_mask);
	sa_dfl.sa_flags = 0;
	
	sigaction(SIGINT, &sa_dfl, NULL);
	sigaction(SIGQUIT, &sa_dfl, NULL);
}