/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:45:22 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/03 20:16:27 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BLUE "\033[1;34m"
#define RESET_COLOR "\033[0m"

void	shell_helper(t_data *data)
{
	data->index = 0;
	data->pipe_index = 0;
	create_pipes(data);
	execute(data);
	close_pipes(data);
	free(data->pid);
	data->pid = NULL;
	remove_heredoc_file(data->env);
}

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

int	start_shell(t_data *data)
{
	while (1)
	{
		init_signals(1);
		data->input = readline(BLUE "Verishen: " RESET_COLOR);
		if (!data->input)
			return (EXIT_FAILURE);
		if (data->input)
			add_history(data->input);
		if (tokenization(data) == EXIT_SUCCESS)
		{
			check_heredoc_limit(data);
			if (create_commands(data) == EXIT_SUCCESS)
			{
				data->pid = malloc(sizeof(int) * (data->pipe_count + 1));
				if (!data->pid)
					return (set_g_exit_status(MALLOC_ERR), EXIT_FAILURE);
				shell_helper(data);
			}
			free_commands(data);
		}
		free_tokens(data);
		free(data->input);
	}
}
