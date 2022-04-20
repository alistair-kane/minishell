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
		write(1, "caught SIGINT\n", 14);
		rl_on_new_line();
		rl_redisplay();
		// todo !!!!! kill(child_pid, SIGKILL);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "caught SIGQUIT\n", 15);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}
