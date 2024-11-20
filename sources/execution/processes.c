/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:45:22 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/20 17:05:09 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BLUE "\033[1;34m"
# define RESET_COLOR "\033[0m"

int start_shell(t_data *data)
{
    while(1)
    {
        data->input = readline(BLUE "Verishen: " RESET_COLOR);
        if(!data->input)
            return (EXIT_FAILURE);
        if (data->input)
            add_history(data->input);
        if(tokenization(data) == EXIT_SUCCESS)
        // if(get_g_exit_status() == EXIT_SUCCESS)
        {
			// create_commands(data);
            if(create_commands(data) == EXIT_SUCCESS)
            {

            // printf("alo -> %d\n", get_g_exit_status());
            data->pid = malloc(sizeof(int) * (data->pipe_count + 1));
            // if(!data->pid)

            data->index = 0;
            data->pipe_index = 0;
            create_pipes(data);
            execute(data);

            // printf("alo -> %d\n", get_g_exit_status());

            // set_g_exit_status(execute(data));
            close_pipes(data);
            remove_heredoc_file(data->env);
            }
            free_commands(data);
        }
        free_tokens(data);
        // system("leaks minishell");
    }
}
