#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../pipex.h"

void	middle_process(t_pipex **piper, char *av, int *fd_in, int *fd_out);
void	run_bonus(t_pipex **piper);

void	here_process(t_pipex **piper, int *fd);
void	run_heredoc(t_pipex **piper);

void	close_unused_pipes(t_pipex **piper, int i);
void	exit_heredoc(t_pipex **piper);

#endif