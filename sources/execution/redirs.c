/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:18:20 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/21 22:01:38 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		minishell_error2(name, "", strerror(errno));
		set_g_exit_status(EXIT_FAILURE);
		return (-1);
	}
	return (fd);
}

int	open_outfile(char *name, int append)
{
	int	fd;

	if (append)
		fd = open(name, O_WRONLY | O_APPEND, 0777);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		minishell_error2(name, "", strerror(errno));
		set_g_exit_status(EXIT_FAILURE);
		return (-1);
	}
	return (fd);
}

void	in_redir(t_data *data)
{
	if (data->commands->stdin > 0)
	{
		if (dup2(data->commands->stdin, 0) < 0)
		{
			minishell_error2("dup2 error", "", "");
			set_g_exit_status(EXIT_FAILURE); // hrcneq chishty verna
		}
		close(data->commands->stdin);
	}
}

void	out_redir(t_data *data)
{
	if (data->commands->stdout > 0)
	{
		if (dup2(data->commands->stdout, 1) < 0)
		{
			minishell_error2("dup2 error", "", "");
			set_g_exit_status(EXIT_FAILURE); // hrcneq chishty verna
		}
		close(data->commands->stdout);
	}
}

void	redir_dups(t_data *data)
{
	in_redir(data);
	out_redir(data);
}

int	open_file_and_remove_token(t_data *data)
{
	if (ft_strcmp(data->current->original_content, ">>") == 0)
	{
		data->current = ft_lst_delone(&data->tokens, data->current);
		data->curr_cmd->stdout = open_outfile(data->current->original_content,
				1);
		if(data->curr_cmd->stdout == -1)
			return (EXIT_FAILURE);
	}
	else if (data->current->original_content[0] == '>')
	{
		data->current = ft_lst_delone(&data->tokens, data->current);
		data->curr_cmd->stdout = open_outfile(data->current->original_content,
				0);
		if(data->curr_cmd->stdout == -1)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(data->current->original_content, "<<") == 0)
	{
		data->current = ft_lst_delone(&data->tokens, data->current);
		data->curr_cmd->stdin = open_heredoc(data->current->original_content);
		if(data->curr_cmd->stdin == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		data->current = ft_lst_delone(&data->tokens, data->current);
		data->curr_cmd->stdin = open_infile(data->current->original_content);
		if(data->curr_cmd->stdin == -1)
			return (EXIT_FAILURE);
	}
	data->current = ft_lst_delone(&data->tokens, data->current);
	return (EXIT_SUCCESS);
}

int	handle_redir(t_data *data)
{
	data->current = data->tokens;
	data->curr_cmd = data->commands;
	while (data->current)
	{
		if(data->current->type == PIPE)
			data->current = data->current->next;
		if (data->current->type == REDIR && data->current->next
			&& (data->current->next->type == REDIR
				|| data->current->next->type == HEREDOC))
		{
			parse_error(data->current->next->original_content);
			set_g_exit_status(2);  //258
			return (EXIT_FAILURE);
		}
		if (data->current->type == REDIR && ((!data->current->next)
				|| data->current->next->type == PIPE))
		{
			parse_error("newline");
			set_g_exit_status(2);  //258
			return (EXIT_FAILURE);
		}
		// else if (data->current && data->current->type == REDIR && !data->current->next)
		// {
		// 	parse_error("IN REDIR");//parse_error(data->current->original_content);
		// 	return (set_g_exit_status(2) , EXIT_FAILURE); //258
		// }
		else if ((data->current->type == REDIR
				|| data->current->type == HEREDOC) && (data->current->next
				&& data->current->next->type == WORD))
		{
			if (open_file_and_remove_token(data))
				return (EXIT_FAILURE);
		}
		else if (data->current)
			data->current = data->current->next;
		else
			break ;
	}
	return (EXIT_SUCCESS);
}
