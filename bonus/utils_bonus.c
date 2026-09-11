#include "pipex_bonus.h"

void	close_unused_pipes(t_pipex **piper, int i)
{
	int	j;

	j = 0;
	while (j < (*piper)->n_pipes)
	{
		if ((i == 0 && j != 0))
			close_all((*piper)->fds[j][0], (*piper)->fds[j][1]);
		else if (i == (*piper)->n_pipes && j != (*piper)->n_pipes - 1)
			close_all((*piper)->fds[j][0], (*piper)->fds[j][1]);
		else if (j != i && j != i - 1)
			close_all((*piper)->fds[j][0], (*piper)->fds[j][1]);
		j++;
	}
}

void	exit_heredoc(t_pipex **piper)
{
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
	exit(0);
}
