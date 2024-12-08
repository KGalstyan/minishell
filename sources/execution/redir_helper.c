/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:37:02 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/08 17:17:29 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	return (fd);
}

int	open_outfile(char *name, int append)
{
	int	fd;

	if (append)
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

void	in_redir(t_data *data)
{
	if (data->curr_cmd->stdin > 0)
	{
		if (dup2(data->curr_cmd->stdin, 0) < 0)
		{
			minishell_error2("dup2 error", "", "");
			set_g_exit_status(EXIT_FAILURE);
		}
		close(data->curr_cmd->stdin);
	}
}

void	out_redir(t_data *data)
{
	if (data->curr_cmd->stdout > 0)
	{
		if (dup2(data->curr_cmd->stdout, 1) < 0)
		{
			minishell_error2("dup2 error", "", "");
			set_g_exit_status(EXIT_FAILURE);
		}
		close(data->curr_cmd->stdout);
	}
}

void	redir_dups(t_data *data)
{
	in_redir(data);
	out_redir(data);
}
