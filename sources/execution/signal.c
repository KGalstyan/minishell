/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:51:02 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/19 19:30:31 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	terminal_config(void)
// {
// 	struct termios	termios_p;

// 	tcgetattr(0, &termios_p);
// 	termios_p.c_lflag &= ~ECHOCTL;
// 	tcsetattr(0, 0, &termios_p);
// }

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	set_g_exit_status(EXIT_FAILURE);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
}

void init_signals(void)
{
	// terminal_config();
    signal(SIGQUIT, handle_sigquit);
    signal(SIGINT, handle_sigint);
}
