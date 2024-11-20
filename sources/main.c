/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:38:59 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/20 17:02:48 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	g_exit_status = 0;

// void set_g_exit_status(int new_status)
// {
//     g_exit_status = new_status;
// }

// int get_g_exit_status()
// {
//     return (g_exit_status);
// }

int main(int argc, char **argv, char **env)
{
    t_data data;
    (void)env;
    // data = malloc(sizeof(data));
    // if(!data)
    //     exit(3);
    init_data(&data, env);
    rl_catch_signals = 0;
	set_g_exit_status(EXIT_SUCCESS);
    if(start_shell(&data))
        printf("exit\n");
    clean_data(&data);
    // system("leaks minishell");
    (void)argc;
    (void)argv;
    return (0);
}
