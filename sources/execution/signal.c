/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:51:02 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/07 22:03:46 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	set_g_exit_status(EXIT_FAILURE);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	write(1, "\n", 1);
	(void)sig;
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

void	back_slash(int sig)
{
	ft_putendl_fd("Quit: 3", 2);
	(void)sig;
}

void	init_signals(int type)
{
	if (type == 1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	else if (type == 3)
	{
		signal(SIGINT, handle_heredoc_sig);
		signal(SIGQUIT, SIG_IGN);
	}
}

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	set_g_exit_status(EXIT_FAILURE);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	handle_sigquit(int sig)
// {
// 	(void)sig;
// 	rl_redisplay();
// }

// void	handle_heredoc_sig(int sig)
// {
// 	(void)sig;
// 	ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	set_g_exit_status(247);
// }

// void	init_signals(int type)
// {
// 	if (type == 1)
// 	{
// 		signal(SIGQUIT, handle_sigquit);
// 		signal(SIGINT, handle_sigint);
// 	}
// 	else if (type == 2)
// 	{
// 		signal(SIGQUIT, handle_sigquit);
// 		signal(SIGINT, handle_heredoc_sig);
// 	}
// }
