/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:34:29 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/21 20:59:31 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dups(t_data *data)
{
	// (void)data;
	if (data->pipe_index != 0 && dup2(data->fd[data->pipe_index - 1][0], 0) ==
		-1)
	{
		close_pipes(data);
		minishell_error("pipe error", "", "");
		exit(1);
	}
	if (data->pipe_index < data->pipe_count
		&& dup2(data->fd[data->pipe_index][1], 1) == -1)
	{
		close_pipes(data);
		// close(data->fd[0][0]);
		minishell_error("pipe error", "", "");
		exit(1);
	}
	close_pipes(data);
}

int		g_exit_status = 0;

void	set_g_exit_status(int new_status)
{
	g_exit_status = new_status;
}

int	get_g_exit_status(void)
{
	return (g_exit_status);
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

int	is_absolute_path(t_data *data)
{
	if (data->commands && data->commands->name
		&& (data->commands->name[0] == '.' || data->commands->name[0] == '/'))
		return (1);
	return (0);
}

void check_and_exec2(t_data *data)
{
	if (access(data->commands->name, F_OK) == 0)
	{
		if(access(data->commands->name, X_OK) == 0)
		{
			execve(data->commands->name, data->commands->args, list_to_array(data->env));
			minishell_error2(data->commands->name, strerror(errno), "");
			exit(127);
		}
		else
		{
			minishell_error2(data->commands->name, "", strerror(errno));
			exit (127);
		}
	}
	minishell_error2(data->commands->name, "", strerror(errno));
	exit (127);
}

bool	is_directory(const char	*path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}

void check_and_exec(t_data *data)
{
	if(is_directory(data->commands->name))
	{
		minishell_error2(data->commands->name, "is a directory", "");
		exit(126);
	}
	if (access(data->commands->name, F_OK) == 0)
	{
		if(access(data->commands->name, X_OK) == 0)
		{
			execve(data->commands->name, data->commands->args, list_to_array(data->env));
			minishell_error2(data->commands->name, strerror(errno), "");
			exit(127);
		}
		else
		{
			minishell_error2(data->commands->name, "", strerror(errno));
			exit (126);
		}
	}
	else
	{
		minishell_error2(data->commands->name, "", strerror(errno));
		exit (127);
	}
}

// char	*get_path(t_data *data)
// {
// 	char	**path_args;
// 	char	*path;

// 	if(is_absolute_path(data))
// 	{
// 		if (access(data->commands->name, F_OK) == 0)
// 		{
// 			if(access(data->commands->name, X_OK) == 0)
// 				return (data->commands->name);
// 			else
// 				return (minishell_error2(data->commands->name, "", strerror(errno)), NULL);
// 		}
// 		else
// 			return (minishell_error2(data->commands->name, "", strerror(errno)), NULL);
// 	}
// 	path_args = ft_split(get_value_from_env(data->env, "PATH"), ':');
// 	if (!path_args)
// 		exit(0);
// 	if (!data->commands->args)
// 			exit(0);
// 	path = get_command_path(path_args, data->commands->name);
// 	free_array(path_args);
// 	return (path);
// }
void get_path_and_execute(t_data *data)
{
	char	**path_args;
	char	*path;

	if(is_absolute_path(data))
		check_and_exec(data);
	path_args = ft_split(get_value_from_env(data->env, "PATH"), ':');
	if (!path_args)
		exit(0);
	if (!data->commands->args)
		exit(0);
	path = get_command_path(path_args, data->commands->name);
	free_array(path_args);
	if(path)
	{
		execve(path, data->commands->args, list_to_array(data->env));
		minishell_error2(data->commands->name, "command not found", "");
		exit(127);
	}
	check_and_exec2(data);
}


int	run_cmd(t_data *data)
{
	data->pid[data->index] = fork();
	if (data->pid[data->index] == -1)
	{
		minishell_error("fork failed", "", "");
		set_g_exit_status(EXIT_FAILURE);
	}
	if (data->pid[data->index] == 0)
	{
		dups(data);
		redir_dups(data);
		if (is_builtin(data->commands->name))
		{
			run_builtin(data, data->commands->args);
			exit(get_g_exit_status());
		}
		get_path_and_execute(data);
	}
	return (data->index++, EXIT_SUCCESS);
}

// int	run_cmd(t_data *data)
// {
// 	char	*path;
// 	char	**path_args;

// 	data->pid[data->index] = fork();
// 	if (data->pid[data->index] == -1)
// 	{
// 		minishell_error("fork failed", "", "");
// 		set_g_exit_status(EXIT_FAILURE);
// 	}
// 	if (data->pid[data->index] == 0)
// 	{
// 		dups(data);
// 		redir_dups(data);
// 		if (is_builtin(data->commands->name))
// 		{
// 			run_builtin(data, data->commands->args);
// 			exit(get_g_exit_status());
// 		}
// 		if (access(data->commands->name, F_OK) == 0)
// 		{
// 			execve(data->commands->name, data->commands->args,
// 				list_to_array(data->env));
// 			minishell_error("command not found", "", data->commands->name);
// 			exit(127);
// 		}
// 		path_args = ft_split(get_value_from_env(data->env, "PATH"), ':');
// 		if (!path_args)
// 			exit(0);
// 		if (!data->commands->args)
// 			exit(0);
// 		path = get_command_path(path_args, data->commands->args[0]);
// 		free_array(path_args);
// 		execve(path, data->commands->args, list_to_array(data->env));
// 		minishell_error("command not found", data->commands->name, "");
// 		exit(127);
// 	}
// 	return (data->index++, EXIT_SUCCESS);
// }

int	run_commands(t_data *data)
{
	if (data->pipe_count == 0)
	{
		if (data->commands && data->commands->name
			&& ft_strcmp(data->commands->name, "exit") == 0)
		{
			// builtin_exit(data);
			return (builtin_exit(data)); // kmtacem der
		}
		if (data->commands && data->commands->name
			&& ft_strcmp(data->commands->name, "cd") == 0)
			return (cd(data, data->commands->args));
		if (data->commands && data->commands->name
			&& ft_strcmp(data->commands->name, "export") == 0)
			return (export(data, data->commands->args));
		if (data->commands && data->commands->name
			&& ft_strcmp(data->commands->name, "unset") == 0)
			return (unset(data, data->commands->args));
	}
	// run_cmd(data);
	return (run_cmd(data));
}

int	execute(t_data *data)
{
	if(!data->tokens)
		return (set_g_exit_status(EXIT_SUCCESS), EXIT_SUCCESS);
	int	k;

	k = 0;
	while (data->pipe_index <= data->pipe_count)
	{
		set_g_exit_status(run_commands(data));
		// free_one_command(data);
		data->pipe_index++;
	}
	close_pipes(data);
	while (k < data->index)
	{
		wait_and_status(data->pid[k], &g_exit_status);
		// waitpid(data->pid[k], NULL, 0);
		k++;
	}
	// printf("alo2 -> %d\n", get_g_exit_status());
	return (EXIT_SUCCESS);
}
