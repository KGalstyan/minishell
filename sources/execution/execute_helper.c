/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:56:26 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/24 21:58:49 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}

int	is_absolute_path(t_data *data)
{
	if (data->commands && data->commands->name
		&& (data->commands->name[0] == '.' || data->commands->name[0] == '/'))
		return (1);
	return (0);
}

void	wait_and_status(pid_t pid, int *_status)
{
	waitpid(pid, _status, 0);
	if (WIFSIGNALED(*_status))
	{
		*_status = WTERMSIG(*_status) + 128;
		if (*_status == 131)
			write(1, "Quit: 3\n", 9);
		return (set_g_exit_status(*_status));
	}
	set_g_exit_status(WEXITSTATUS(*_status));
}

void	clean_exit(t_data *data, int status)
{
	clean_data(data);
	exit(status);
}

void	dups(t_data *data)
{
	if (data->pipe_index != 0 && dup2(data->fd[data->pipe_index - 1][0], 0) ==
		-1)
	{
		close_pipes(data);
		minishell_error("pipe error", "", "");
		clean_exit(data, 1);
	}
	if (data->pipe_index < data->pipe_count
		&& dup2(data->fd[data->pipe_index][1], 1) == -1)
	{
		close_pipes(data);
		minishell_error("pipe error", "", "");
		clean_exit(data, 1);
	}
	close_pipes(data);
}
