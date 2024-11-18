/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brakets_insertion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:59:12 by kgalstya          #+#    #+#             */
/*   Updated: 2024/11/18 17:50:10 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void connect_content(t_data *data, t_ptr *ptr, enum s_quotes quotes_num)
{
	while (data->current && (data->current->quotes == quotes_num))
	{
		if (data->current->quotes != quotes_num && ptr->first != ptr->last)
		{
			data->current = connect_lst_in_one(&data->tokens, ptr->first, ptr->last, WORD);
			continue ;
		}
		ptr->last = data->current;
		data->current = data->current->next;
	}
}
void	single_string_insertion(t_data *data)
{
	t_ptr ptr;

	data->current = data->tokens;
	while (data->current)
	{
		if (data->current->quotes == SINGLE)
		{
			ptr.first = data->current;
			ptr.last = data->current;
			connect_content(data, &ptr, SINGLE);
			data->current = connect_lst_in_one(&data->tokens, ptr.first, ptr.last,
					WORD);
		}
		if (data->current && data->current->next)
			data->current = data->current->next;
		else
			return ;
	}
}

void	double_string_insertion(t_data *data)
{
	t_ptr ptr;

	data->current = data->tokens;
	while (data->current)
	{
		if (data->current->quotes == DOUBLE)
		{
			ptr.first = data->current;
			ptr.last = data->current;
			connect_content(data, &ptr, DOUBLE);
			data->current = connect_lst_in_one(&data->tokens, ptr.first, ptr.last,
					WORD);
		}
		if (data->current && data->current->next)
			data->current = data->current->next;
		else
			return ;
	}
}

void	remove_brakets(t_data *data)
{
	data->current = data->tokens;
	while (data->current)
	{
		if (data->current->original_content[0] == '\''
			&& data->current->quotes == 1)
			data->current = ft_lst_delone(&data->tokens, data->current);
		else if (data->current->original_content[0] == '"'
			&& data->current->quotes == 2)
			data->current = ft_lst_delone(&data->tokens, data->current);
		else
			data->current = data->current->next;
	}
}
