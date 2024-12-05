/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:57:57 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/03 20:16:44 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_and_exec2(t_data *data)
{
	if (access(data->curr_cmd->name, F_OK) == 0)
	{
		if (access(data->curr_cmd->name, X_OK) == 0)
		{
			execve(data->curr_cmd->name, data->curr_cmd->args,
				list_to_array(data->env));
			minishell_error2(data->curr_cmd->name, strerror(errno), "");
			clean_exit(data, 127);
		}
		else
		{
			minishell_error2(data->curr_cmd->name, "", strerror(errno));
			clean_data(data);
			exit(127);
		}
	}
	minishell_error2(data->curr_cmd->name, "", strerror(errno));
	clean_data(data);
	exit(127);
}

void	check_and_exec(t_data *data)
{
	if (is_directory(data->curr_cmd->name))
	{
		minishell_error2(data->curr_cmd->name, "is a directory", "");
		clean_exit(data, 126);
	}
	if (access(data->curr_cmd->name, F_OK) == 0)
	{
		if (access(data->curr_cmd->name, X_OK) == 0)
		{
			execve(data->curr_cmd->name, data->curr_cmd->args,
				list_to_array(data->env));
			minishell_error2(data->curr_cmd->name, strerror(errno), "");
			clean_exit(data, 127);
		}
		else
		{
			minishell_error2(data->curr_cmd->name, "", strerror(errno));
			clean_exit(data, 126);
		}
	}
	else
	{
		minishell_error2(data->curr_cmd->name, "", strerror(errno));
		clean_exit(data, 127);
	}
}

void	get_path_and_execute(t_data *data)
{
	char	**path_args;
	char	*path;

	if (is_absolute_path(data))
		check_and_exec(data);
	if (!data->curr_cmd->args)
		clean_exit(data, 0);
	path_args = ft_split(get_value_from_env(data->env, "PATH"), ':');
	if (!path_args)
	{
		minishell_error2(data->curr_cmd->name, "command not found", "");
		clean_exit(data, 127);
	}
	path = get_command_path(path_args, data->curr_cmd->name);
	free_array(path_args);
	if (path)
	{
		execve(path, data->curr_cmd->args, list_to_array(data->env));
		minishell_error2(data->curr_cmd->name, "command not found", "");
		clean_exit(data, 127);
	}
	check_and_exec2(data);
}
