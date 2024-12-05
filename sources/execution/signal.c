/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:51:02 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/02 16:39:18 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_heredoc_sig(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	set_g_exit_status(247);
}

void	init_signals(int type)
{
	if (type == 1)
	{
		signal(SIGQUIT, handle_sigquit);
		signal(SIGINT, handle_sigint);
	}
	else if (type == 2)
	{
		signal(SIGQUIT, handle_sigquit);
		signal(SIGINT, handle_heredoc_sig);
	}
}
