/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_insertion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:10:02 by kgalstya          #+#    #+#             */
/*   Updated: 2024/12/02 16:25:01 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(t_data *data, t_token *first, t_token *last)
{
	if (data->current->next && data->current->quotes == 0
		&& (data->current->original_content
			&& data->current->original_content[0] == '>'
			&& data->current->next->original_content[0] == '>'))
	{
		if (data->current->next->quotes == 0)
		{
			last = data->current->next;
			data->current = connect_lst_in_one(&data->tokens, first, last,
					REDIR);
			if (!data->current)
				return (set_g_exit_status(MALLOC_ERR), 2);
			return (1);
		}
	}
	return (0);
}

int	redir_helper(t_data *data, t_token *first, t_token *last, int check_status)
{
	while (data->current)
	{
		first = data->current;
		check_status = check_redir(data, first, last);
		if (check_status == 1)
			continue ;
		else if (check_status == 2)
			return (EXIT_FAILURE);
		if (data->current)
			data->current = data->current->next;
		else
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int	redir_insertion(t_data *data)
{
	t_token	*first;
	t_token	*last;
	int		check_status;

	last = NULL;
	first = NULL;
	check_status = 0;
	data->current = data->tokens;
	if (data->current && data->current->quotes == 0
		&& (data->current->original_content[0] == '>'
			|| data->current->original_content[0] == '<'))
	{
		data->current->type = REDIR;
		if (!data->current->next)
		{
			parse_error("newline");
			return (set_g_exit_status(2), EXIT_FAILURE); // 258
		}
	}
	if (redir_helper(data, first, last, check_status))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	space_insertion(t_data *data)
{
	data->current = data->tokens;
	while (data->current)
	{
		if (data->current && data->current->type == REDIR && data->current->next
			&& data->current->next->type == SPACEO && data->current->next->next
			&& data->current->next->next->type == REDIR)
		{
			parse_error(data->current->original_content);// ||
			return (set_g_exit_status(2), EXIT_FAILURE);// 258
		}
		data->current = data->current->next;
	}
	if (connect_tokens(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	data->current = data->tokens;
	while (data->current)
	{
		if (data->current->type == SPACEO && data->current->quotes == 0)
			data->current = ft_lst_delone(&data->tokens, data->current);
		else
			data->current = data->current->next;
	}
	return (EXIT_SUCCESS);
}

int	tokens_insertion(t_data *data)
{
	remove_brakets(data);
	if (single_string_insertion(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (dollar_insertion(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (double_string_insertion(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (redir_insertion(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (space_insertion(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (heredoc_insertion(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (pipe_insertion(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
