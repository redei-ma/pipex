#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	*piper;

	if (ac != 5)
		return (ft_fprintf(2, "Input: <infile> <cmd1> <cmd2> <outfile>\n"));
	if (!envp)
		return (ft_fprintf(2, "envp not found"));
	piper = ft_calloc(1, sizeof(t_pipex));
	if (!piper)
		return (ft_fprintf(2, "malloc failed"));
	set_piper(&piper, ac, av, envp);
	run(&piper);
	close_pipes(piper->fds, piper->n_pipes);
	ft_free_mat((void *)piper->fds, piper->n_pipes);
	free(piper->pids);
	free(piper);
	while (wait(NULL) > 0)
		;
	return (0);
}
