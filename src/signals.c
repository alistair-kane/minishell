// !!!!!

#include <signal.h>
#include "../minishell.h"

// CTRL + d -> not a signal (closes stdin) -> catch with read()?
// SIGINT (interrupt) CTRL + c
// SIGQUIT (quit) CTRL + '\'

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}
