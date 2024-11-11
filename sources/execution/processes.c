/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:45:22 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/11 21:10:42 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
////// khanes sa /////
#define BLUE "\033[1;34m"
# define RESET_COLOR "\033[0m"

int start_shell(t_data *data)
{
    init_signals();
    while(1)
    {
        data->input = readline(BLUE "Verishen: " RESET_COLOR);
        if (data->input)
            add_history(data->input);
		if (!data->input)
			return(1);
        tokenization(data);
        print_data(data);
		if(get_g_exit_status() == EXIT_SUCCESS)
			create_commands(data);
        printf("✅ CORRECT INPUT\n");
        free_tokens(data);
        //("leaks minishell");
    }
	return(0);
}
