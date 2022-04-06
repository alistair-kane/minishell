// !!!!! add header

// will have to take the exit status from pipe later on maybe...?

#include "../../minishell.h"

void	builtin_exit(int status)
{
	exit(status);
}