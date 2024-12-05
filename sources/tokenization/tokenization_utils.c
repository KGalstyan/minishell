/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/02 16:22:53 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_data *data)
{
	t_token	*next;

	data->current = data->tokens;
	while (data->current)
	{
		next = data->current->next;
		if (data->current->original_content)
		{
			free(data->current->original_content);
			data->current->original_content = NULL;
		}
		free(data->current);
		data->current = next;
	}
	data->tokens = NULL;
}

int	fill_tokens(t_data *data, int i, int j, int quotes)
{
	t_token	*token1;

	if (i - j <= 0)
		return (0);
	token1 = ft_lstnew(quotes);
	if (!token1)
	{
		set_g_exit_status(MALLOC_ERR);
		return (EXIT_FAILURE);
	}
	token1->original_content = ft_strndup(data->input, i, j);
	token1->type = data->type;
	if (!token1->original_content)
	{
		free(token1);
		set_g_exit_status(MALLOC_ERR);
		return (EXIT_FAILURE);
	}
	ft_lstadd_back(&data->tokens, token1);
	return (EXIT_SUCCESS);
}

int	check_pipe_red_env(t_data *data)
{
	if (data->input[data->i] == '|')
	{
		data->i++;
		data->type = PIPE;
		fill_tokens(data, data->i, data->j, data->quotes_flag);
		return (1);
	}
	else if (data->input[data->i] == '>' || data->input[data->i] == '<')
	{
		data->i++;
		data->type = REDIR;
		fill_tokens(data, data->i, data->j, data->quotes_flag);
		return (1);
	}
	else if (data->input[data->i] == '$')
	{
		data->i++;
		data->type = WORD;
		fill_tokens(data, data->i, data->j, data->quotes_flag);
		return (1);
	}
	return (0);
}

int	check_quotes(t_data *data)
{
	if (data->input[data->i] == '"')
	{
		data->i++;
		data->quotes_flag = DOUBLE;
		data->type = WORD;
		fill_tokens(data, data->i, data->j, data->quotes_flag);
		return (1);
	}
	else if (data->input[data->i] == '\'')
	{
		data->i++;
		data->quotes_flag = SINGLE;
		data->type = WORD;
		fill_tokens(data, data->i, data->j, data->quotes_flag);
		return (1);
	}
	return (0);
}

int	check_space(t_data *data)
{
	while (data->input[data->i] && data->input[data->i] == ' ')
		data->i++;
	if (data->input[data->j] == ' ')
	{
		data->type = SPACEO;
		fill_tokens(data, data->i, data->j, data->quotes_flag);
		return (1);
	}
	return (0);
}
