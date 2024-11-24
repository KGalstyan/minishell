/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:45:22 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/24 18:33:53 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BLUE "\033[1;34m"
# define RESET_COLOR "\033[0m"

int start_shell(t_data *data)
{
    while(1)
    {
        init_signals(1);
        data->input = readline(BLUE "Verishen: " RESET_COLOR);
        if(!data->input)
            return (EXIT_FAILURE);
        if (data->input)
            add_history(data->input);
        if(tokenization(data) == EXIT_SUCCESS)
        {
            // create_commands(data);
            if(create_commands(data) == EXIT_SUCCESS)
            {
                // print_a(data);
                data->pid = malloc(sizeof(int) * (data->pipe_count + 1));
                if(!data->pid)
                    return(set_g_exit_status(MALLOC_ERR), EXIT_FAILURE);
                data->index = 0;
                data->pipe_index = 0;
                create_pipes(data);
                execute(data);
                close_pipes(data);
                // free(data->fd);
                // data->fd = NULL;
                free(data->pid);
                data->pid = NULL;
                remove_heredoc_file(data->env);
            }
            free_commands(data);
        }
        free_tokens(data);
        free(data->input);
        // system("leaks minishell");
    }
}
