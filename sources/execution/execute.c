/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:34:29 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/17 03:15:40 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dups(t_data *data)
{
	// (void)data;
	if (data->pipe_index != 0 && dup2(data->fd[data->pipe_index - 1][0], 0) == -1)
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



// void	dupeing(t_pipex *pipex, t_cmd *cmd)
// {
// 	if (cmd->input != 0)
// 	{
// 		if (dup2(cmd->input, 0) == -1)
// 			p_error(pipex, DUP_ERR, NULL, 1);
// 		close(cmd->input);
// 	}
// 	if (cmd->output != 1)
// 	{
// 		if (dup2(cmd->output, 1) == -1)
// 			p_error(pipex, DUP_ERR, NULL, 1);
// 		close(cmd->output);
// 	}
// 	close_pipes(pipex);
// }

int	run_cmd(t_data *data)
{

	char	*path;
	char	**path_args;
	(void)path;
	(void)path_args;

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
		// //rediri duper
		if (is_builtin(data->commands->name))
		{
			run_builtin(data, data->commands->args);
			exit(1);
		}
		if(access(data->commands->name, F_OK) == 0)
		{
			execve(data->commands->name, data->commands->args, list_to_array(data->env));
			minishell_error("command not found", "", data->commands->name);
			exit(1);
		}
		path_args = ft_split(get_value_from_env(data->env, "PATH"), ':');
		if(!path_args)
			exit(1);
		if(!data->commands->args)
			exit(1);
		path = get_command_path(path_args, data->commands->args[0]);
		free_array(path_args);
		execve(path, data->commands->args, list_to_array(data->env));
		minishell_error("command not found", "", data->commands->name);
		exit(1);
	}
	return (data->index++, EXIT_SUCCESS);
}
// int	run_commands(t_data *data)
// {
// 	if (data->pipe_count == 0)
// 	{
// 	    if(data->commands->args[0] && is_builtin(data->commands->name))
// 	        run_builtin(data, data->commands->args);
// 	}
// 	run_cmd(data);
// 	return (EXIT_SUCCESS);
// }

int	execute(t_data *data)
{
	while (data->pipe_index <= data->pipe_count)
	{
		run_cmd(data);
		// close(data->curr_cmd->stdin);
		free_one_command(data);
		// data->commands = data->commands->next;
		// free one command
		data->pipe_index++;
	}
	close_pipes(data);
	// if (data->pipe_index == 0)
	// 	run_cmd(data);
	// int a;
	int k = 0;
	while (k < data->index)
	{
		waitpid(data->pid[k], NULL, 0);
		k++;
	}
	
	// (void)data;
	// // print_a(data);
	// // char **args;
	// // if (!data->commands)
	// // 	return (0);
	// // args = tokens_to_matrix(data);
	// if(data->commands->args[0] && is_builtin(data->commands->name))
	//     run_builtin(data, data->commands->args);
	// else
	//     run_cmd(data, data->commands->args);
	// // free_array(args);
	return (EXIT_SUCCESS);
}
