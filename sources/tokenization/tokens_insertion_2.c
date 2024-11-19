/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_insertion_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:10:02 by kgalstya          #+#    #+#             */
/*   Updated: 2024/11/19 22:53:49 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void make_new_cont(t_data *data, t_div	*div, char	*new_cont)
{
	div->i++;
	new_cont = ft_substr(data->current->original_content, div->i, ft_strlen(data->current->original_content));
	free(data->current->original_content);
	data->current->original_content = new_cont;
}

int	connect_tokens(t_data *data)
{
	t_token	*first;
	t_token	*last;

	data->current = data->tokens;
	first = data->current;
	last = data->current;
	while (data->current)
	{
		last = data->current;
		first = data->current;
		while (data->current && (data->current->type != SPACEO
				&& data->current->type != PIPE && data->current->type != REDIR))
		{
			last = data->current;
			if (data->current->next)
				data->current = data->current->next;
			else
				break ;
		}
		if (last != first)
		{
			data->current = connect_lst_in_one(&data->tokens, first, last,
					WORD);
			if(!data->current)
				return(set_g_exit_status(MALLOC_ERR), EXIT_FAILURE);
		}
		else if (data->current->next)
			data->current = data->current->next;
		else
			return(EXIT_SUCCESS);
	}
	return(EXIT_SUCCESS);
}

int	space_insertion(t_data *data)
{
	if(connect_tokens(data) != EXIT_SUCCESS)
		return(EXIT_FAILURE);
	data->current = data->tokens;
	while (data->current)
	{
		if (data->current->type == SPACEO && data->current->quotes == 0)
			data->current = ft_lst_delone(&data->tokens, data->current);
		///// poxel yst anhrajeshtutyan /////
		else
			data->current = data->current->next;
	}
	return(EXIT_SUCCESS);
}

int	pipe_insertion(t_data *data)
{
	data->current = data->tokens;
	if (data->current && data->current->type == PIPE)
	{
		parse_error("|");
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
			&& (data->current->next->type == PIPE || data->current->next->type == REDIR || data->current->next->type == HEREDOC))
		{
			parse_error("|");
			return (set_g_exit_status(2) , EXIT_FAILURE);//258
		}
		data->current = data->current->next;
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
				if (!data->current)
					return (set_g_exit_status(MALLOC_ERR), EXIT_FAILURE);
				continue ;
			}
		}
		if (data->current)
			data->current = data->current->next;
	}
	return(EXIT_SUCCESS);
}
