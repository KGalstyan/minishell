/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:34:29 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/07 22:49:44 by vkostand         ###   ########.fr       */
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

int	run_cmd(t_data *data)
{
	init_signals(2);
	data->pid[data->index] = fork();
	if (data->pid[data->index] == -1)
	{
		set_g_exit_status(EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (data->pid[data->index] == 0)
	{
		if (data->curr_cmd->error)
			handle_error(data);
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
