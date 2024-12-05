/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:34:29 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/03 20:35:21 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;

void	set_g_exit_status(int new_status)
{
	g_exit_status = new_status;
}

int	get_g_exit_status(void)
{
	return (g_exit_status);
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
// 				return (minishell_error2(data->commands->name, "",
// strerror(errno)), NULL);
// 		}
// 		else
// 			return (minishell_error2(data->commands->name, "", strerror(errno)),
// NULL);
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

int	run_cmd(t_data *data)
{
	data->pid[data->index] = fork();
	if (data->pid[data->index] == -1)
	{
		set_g_exit_status(EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (data->pid[data->index] == 0)
	{
		dups(data);
		redir_dups(data);
		if (data->curr_cmd->name && is_builtin(data->curr_cmd->name))
		{
			run_builtin(data, data->curr_cmd->args);
			clean_data(data);
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
		if (data->curr_cmd && data->curr_cmd->name
			&& ft_strcmp(data->curr_cmd->name, "exit") == 0)
		{
			return (builtin_exit(data));
		}
		if (data->curr_cmd && data->curr_cmd->name
			&& ft_strcmp(data->curr_cmd->name, "cd") == 0)
			return (cd(data, data->curr_cmd->args));
		if (data->curr_cmd && data->curr_cmd->name
			&& ft_strcmp(data->curr_cmd->name, "export") == 0)
			return (export(data, data->curr_cmd->args));
		if (data->curr_cmd && data->curr_cmd->name
			&& ft_strcmp(data->curr_cmd->name, "unset") == 0)
			return (unset(data, data->curr_cmd->args));
	}
	return (run_cmd(data));
}

// void	kill_processes(t_data *data)
// {
// 	int	index;

// 	index = 0;
// 	while (index < data->index)
// 	{
// 		kill(data->pid[index], SIGKILL);
// 		index++;
// 	}
// }

int	execute(t_data *data)
{
	int	k;

	if (!data->tokens)
		return (set_g_exit_status(EXIT_SUCCESS), EXIT_SUCCESS);
	data->curr_cmd = data->commands;
	while (data->pipe_index <= data->pipe_count)
	{
		set_g_exit_status(run_commands(data));
		data->curr_cmd = data->curr_cmd->next;
		data->pipe_index++;
	}
	close_pipes(data);
	k = 0;
	while (k < data->index)
	{
		wait_and_status(data->pid[k], &g_exit_status);
		k++;
	}
	return (EXIT_SUCCESS);
}
