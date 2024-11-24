/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_insertion_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:10:02 by kgalstya          #+#    #+#             */
/*   Updated: 2024/11/24 22:00:01 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int check_connecting(t_token *current, t_ptr *ptr)
// {
// 	while (current && (current->type != SPACEO
// 				&& current->type != PIPE && current->type != REDIR))
// 	{
// 		ptr->last = current;
// 		if (current->next)
// 			current = current->next;
// 		else
// 			return(1) ;
// 	}
// 	return(0);
// }
int check_connecting(t_data *data, t_ptr *ptr)
{
	if (ptr->last != ptr->first)
	{
		data->current = connect_lst_in_one(&data->tokens, ptr->first, ptr->last,
			WORD);
		if(!data->current)
			return(set_g_exit_status(MALLOC_ERR), EXIT_FAILURE);
	}
	else if (data->current->next)
	{
			data->current = data->current->next;
			return(3);
	}
	return(EXIT_SUCCESS);
}

// int	connect_tokens(t_data *data)
// {
// 	t_ptr ptr;

// 	data->current = data->tokens;
// 	ptr.first = data->current;
// 	ptr.last = data->current;
// 	while (data->current)
// 	{
// 		ptr.last = data->current;
// 		ptr.first = data->current;
// 		if(check_connecting(data, &ptr))
// 			break ;
// 		if (ptr.last != ptr.first)
// 		{
// 			data->current = connect_lst_in_one(&data->tokens, ptr.first, ptr.last,
// 					WORD);
// 			if(!data->current)
// 				return(set_g_exit_status(MALLOC_ERR), EXIT_FAILURE);
// 		}
// 		else if (data->current->next)
// 			data->current = data->current->next;
// 		else
// 			return(EXIT_SUCCESS);
// 	}
// 	return(EXIT_SUCCESS);
// }
int	connect_tokens(t_data *data)
{
	t_ptr ptr;
	int status;

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
		if(status != 3)
			return(status);
	}
	return(EXIT_SUCCESS);
}

int	pipe_insertion(t_data *data)
{
	data->current = data->tokens;
	if (data->current && data->current->type == PIPE)
	{
		parse_error("|"); // ||
		return (set_g_exit_status(2) , EXIT_FAILURE);//258
	}
	while (data->current)
	{
		if (data->current->type == PIPE && (!data->current->next))
		{
			parse_error("|");
			return (set_g_exit_status(2) , EXIT_FAILURE);//258
		}
		if (data->current->type == PIPE && data->current->next
			&& (data->current->next->type == HEREDOC))
		{
			parse_error("newline");
			return (set_g_exit_status(2) , EXIT_FAILURE);//258
		}
		data->current = data->current->next;
	}
	return (EXIT_SUCCESS);
}

int check_heredoc(t_data *data)
{
	if (!data->current)
		return (set_g_exit_status(MALLOC_ERR), EXIT_FAILURE);
	if(!data->current->next)
	{
		parse_error("newline");
		return(set_g_exit_status(2), EXIT_FAILURE); //258
	}
	else if(data->current->next->type == PIPE)
	{
		parse_error("|");
		return(set_g_exit_status(2), EXIT_FAILURE); //258
	}
	return(EXIT_SUCCESS);
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
				if(check_heredoc(data) == EXIT_FAILURE)
					return(EXIT_FAILURE);
				continue ;
			}
		}
		if (data->current)
			data->current = data->current->next;
	}
	return(EXIT_SUCCESS);
}
