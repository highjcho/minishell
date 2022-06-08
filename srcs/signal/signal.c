#include "../../includes/signal.h"

void	handle_signal(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
	{
		if (pid == -1)
		{	

			rl_on_new_line();
			printf("\n");
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			printf("^C\n");
	}
	else if (signum == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else
			printf("Quit: 3\n");
	}
}

void	handle_signal_heredoc(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
	{
		if (signum == SIGINT)
			exit(1);
		else if (signum == SIGQUIT)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else
	{
		if (signum == SIGINT)
			printf("\n");
		else if (signum == SIGQUIT)
		{
		}
	}
}

void	signal_init(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}