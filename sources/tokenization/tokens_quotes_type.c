/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_quotes_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:04:04 by kgalstya          #+#    #+#             */
/*   Updated: 2024/12/02 16:23:20 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes_close(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (data->input[i] && data->input[i] == '\'')
		{
			i++;
			while (data->input[i] && data->input[i] != '\'')
				i++;
			if (!data->input[i])
				return (parse_error("'"), EXIT_FAILURE);
		}
		else if (data->input[i] && data->input[i] == '"')
		{
			i++;
			while (data->input[i] && data->input[i] != '"')
				i++;
			if (!data->input[i])
				return (parse_error("\""), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	allot_double_quotes_value(t_data *data)
{
	int	i;

	i = 0;
	if (data->current->next)
		data->current = data->current->next;
	if (data->current && data->current->original_content[i] == '"')
	{
		data->current->quotes = DOUBLE;
		data->current = data->current->next;
		return (1);
	}
	while (data->current && data->current->original_content[i] != '"')
	{
		data->current->quotes = DOUBLE;
		data->current = data->current->next;
	}
	if (data->current && data->current->original_content[i] == '"')
	{
		data->current->quotes = DOUBLE;
		data->current = data->current->next;
	}
	return (1);
}

static int	allot_single_quotes_value(t_data *data)
{
	int	i;

	i = 0;
	if (data->current->next)
		data->current = data->current->next;
	if (data->current && data->current->original_content[i] == '\'')
	{
		data->current->quotes = SINGLE;
		data->current = data->current->next;
		return (1);
	}
	while (data->current && data->current->original_content[i] != '\'')
	{
		data->current->quotes = SINGLE;
		data->current = data->current->next;
	}
	if (data->current && data->current->original_content[i] == '\'')
	{
		data->current->quotes = SINGLE;
		data->current = data->current->next;
	}
	return (1);
}

int	allot_quotes_value(t_data *data)
{
	int	i;

	i = 0;
	data->current = data->tokens;
	if (check_quotes_close(data))
		return (set_g_exit_status(EXIT_FAILURE), EXIT_FAILURE);
	while (data->current)
	{
		if (data->current->original_content[i] == '"')
			allot_double_quotes_value(data);
		else if (data->current->original_content[i] == '\'')
			allot_single_quotes_value(data);
		else
		{
			data->current->quotes = NONE;
			data->current = data->current->next;
		}
	}
	data->current = NULL;
	return (EXIT_SUCCESS);
}
