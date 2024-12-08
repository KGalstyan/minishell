/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:45:22 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/07 22:56:17 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BLUE "\033[1;34m"
#define RESET_COLOR "\033[0m"

void	check_heredoc_limit(t_data *data)
{
	int	here_count;

	here_count = 0;
	data->current = data->tokens;
	while (data->current)
	{
		if (data->current->type == HEREDOC)
			here_count++;
		data->current = data->current->next;
	}
	if (here_count > 16)
	{
		minishell_error2("maximum here-document count exceeded", "", "");
		free_tokens(data);
		free(data->input);
		clean_data(data);
		set_g_exit_status(2);
		exit(2);
	}
}

void	shell_helper(t_data *data)
{
	data->index = 0;
	data->pipe_index = 0;
	create_pipes(data);
	execute(data);
	close_pipes(data);
	free(data->pid);
	data->pid = NULL;
	remove_heredoc_file();
}

void	free_in_loop(t_data *data)
{
	if (data->commands)
		free_commands(data);
	if (data->error)
	{
		free(data->error);
		data->error = NULL;
	}
	if (data->tokens)
		free_tokens(data);
	if (data->input)
		free(data->input);
}

void	shell_helper2(t_data *data)
{
	if (data->input)
		add_history(data->input);
	tokenization(data);
	check_heredoc_limit(data);
	create_commands(data);
}

int	start_shell(t_data *data)
{
	rl_catch_signals = 0;
	while (1)
	{
		init_signals(1);
		data->input = readline(BLUE "Verishen: " RESET_COLOR);
		if (!data->input)
			return (EXIT_FAILURE);
		shell_helper2(data);
		if (get_g_exit_status() == 247)
		{
			remove_heredoc_file();
			set_g_exit_status(1);
		}
		else if (data->error)
			write(STDERR_FILENO, data->error, ft_strlen(data->error));
		else
		{
			data->pid = malloc(sizeof(int) * (data->pipe_count + 1));
			if (!data->pid)
				return (set_g_exit_status(MALLOC_ERR), EXIT_FAILURE);
			shell_helper(data);
		}
		free_in_loop(data);
	}
}
