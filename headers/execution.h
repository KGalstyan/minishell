/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:27:50 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/11 16:27:35 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

struct s_command
{
	char *name;
	char **args;
	t_command *next;
};

int start_shell(t_data *data);

////////////   signals    ////////////
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	init_signals(void);
int		create_commands(t_data *data);
void	ft_lstadd_back_cmd(t_command **lst, t_command *new);





#endif
