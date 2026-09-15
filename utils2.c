#include "pipex.h"

static void	free_all(char **mat, char *str)
{
	if (mat)
		ft_free_mat((void **)mat, 2);
	if (str)
		free(str);
}

void	exit_error(char *msg, t_pipex **piper, char **cmd, char *path)
{
	ft_fprintf(2, "%s\n", msg);
	if (piper)
	{
		if ((*piper)->fds)
		{
			if ((*piper)->i > 0)
				close_pipes((*piper)->fds, (*piper)->n_pipes);
			ft_free_mat((void *)(*piper)->fds, (*piper)->n_pipes);
		}
		if ((*piper)->pids)
			free((*piper)->pids);
		free(*piper);
	}
	free_all(cmd, path);
	exit(1);
}

void	close_all(int fd1, int fd2)
{
	safe_close(&fd1);
	safe_close(&fd2);
}

void	close_pipes(int **fds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (fds[i])
			close_all(fds[i][0], fds[i][1]);
		i++;
	}
}
