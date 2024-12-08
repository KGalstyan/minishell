/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_insertion_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:10:02 by kgalstya          #+#    #+#             */
/*   Updated: 2024/12/06 18:12:19 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_insertion_2(t_data *data)
{
	data->current = data->tokens;
	if (data->current && data->current->type == PIPE)
	{
		data->error = parse_error("|");
		if (!data->error)
			return (set_g_exit_status(MALLOC_ERR), MALLOC_ERR);
		return (set_g_exit_status(258), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	pipe_insertion(t_data *data)
{
	int	tmp;

	tmp = pipe_insertion_2(data);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	while (data->current)
	{
		if (data->current->type == PIPE && (!data->current->next))
		{
			data->error = parse_error("|");
			if (!data->error)
				return (set_g_exit_status(MALLOC_ERR), MALLOC_ERR);
			return (set_g_exit_status(258), EXIT_FAILURE);
		}
		if (data->current->type == PIPE && data->current->next
			&& (data->current->next->type == HEREDOC))
		{
			data->error = parse_error("newline");
			if (!data->error)
				return (set_g_exit_status(MALLOC_ERR), MALLOC_ERR);
			return (set_g_exit_status(258), EXIT_FAILURE);
		}
		data->current = data->current->next;
	}
	return (EXIT_SUCCESS);
}

int	check_heredoc(t_data *data)
{
	if (!data->current)
		return (set_g_exit_status(MALLOC_ERR), EXIT_FAILURE);
	if (!data->current->next)
	{
		data->error = parse_error("newline");
		if (!data->error)
			return (set_g_exit_status(MALLOC_ERR), MALLOC_ERR);
		return (set_g_exit_status(258), EXIT_FAILURE);
	}
	else if (data->current->next->type == PIPE)
	{
		data->error = parse_error("|");
		if (!data->error)
			return (set_g_exit_status(MALLOC_ERR), MALLOC_ERR);
		return (set_g_exit_status(258), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	heredoc_insertion(t_data *data)
{
	t_token	*first;
	t_token	*last;

	data->current = data->tokens;
	while (data->current)
	{
		first = data->current;
		if (data->current->next && data->current->quotes == 0
			&& (data->current->original_content[0] == '<'
				&& data->current->next->original_content[0] == '<'))
		{
			if (data->current->next->quotes == 0)
			{
				last = data->current->next;
				data->current = connect_lst_in_one(&data->tokens, first, last,
						HEREDOC);
				if (check_heredoc(data) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				continue ;
			}
		}
		if (data->current)
			data->current = data->current->next;
	}
	return (EXIT_SUCCESS);
}
