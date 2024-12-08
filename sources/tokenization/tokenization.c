/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/06 17:56:14 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_connecting(t_data *data, t_ptr *ptr)
{
	if (ptr->last != ptr->first)
	{
		data->current = connect_lst_in_one(&data->tokens, ptr->first, ptr->last,
				WORD);
		if (!data->current)
			return (set_g_exit_status(MALLOC_ERR), EXIT_FAILURE);
	}
	else if (data->current->next)
	{
		data->current = data->current->next;
		return (3);
	}
	return (EXIT_SUCCESS);
}

int	connect_tokens(t_data *data)
{
	t_ptr	ptr;
	int		status;

	data->current = data->tokens;
	ptr.first = data->current;
	ptr.last = data->current;
	while (data->current)
	{
		ptr.last = data->current;
		ptr.first = data->current;
		while (data->current && (data->current->type != SPACEO
				&& data->current->type != PIPE && data->current->type != REDIR))
		{
			ptr.last = data->current;
			if (data->current->next)
				data->current = data->current->next;
			else
				break ;
		}
		status = check_connecting(data, &ptr);
		if (status != 3)
			return (status);
	}
	return (EXIT_SUCCESS);
}

int	check_special_tokens(t_data *data)
{
	if (data->input[data->i] == '<' || data->input[data->i] == '>')
		return (1);
	else if (data->input[data->i] == '$' || data->input[data->i] == '|')
		return (1);
	else if (data->input[data->i] == '"' || data->input[data->i] == '\'')
		return (1);
	return (0);
}

int	create_tokens(t_data *data)
{
	data->i = 0;
	data->j = 0;
	while (data->input[data->i])
	{
		data->quotes_flag = NONE;
		data->j = data->i;
		if (check_pipe_red_env(data))
			continue ;
		else if (check_quotes(data))
			continue ;
		else if (check_space(data))
			continue ;
		while (data->input[data->i] && data->input[data->i] != ' ')
		{
			if (check_special_tokens(data))
				break ;
			data->i++;
		}
		data->type = WORD;
		if (fill_tokens(data, data->i, data->j,
				data->quotes_flag) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	tokenization(t_data *data)
{
	if (create_tokens(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (allot_quotes_value(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (tokens_insertion(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
