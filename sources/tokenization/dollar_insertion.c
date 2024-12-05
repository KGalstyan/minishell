/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_insertion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:26:31 by kgalstya          #+#    #+#             */
/*   Updated: 2024/12/02 16:24:25 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env(t_data *data, t_div *div, char *new_cont)
{
	if (ft_isalpha(data->current->original_content[div->i])
		|| ft_isdigit(data->current->original_content[div->i])
		|| data->current->original_content[div->i] == '_')
	{
		if (ft_isdigit(data->current->original_content[div->i]) && div->i == 0)
		{
			make_new_cont(data, div, new_cont);
			return (1);
		}
		while (ft_isalpha(data->current->original_content[div->i])
			|| ft_isdigit(data->current->original_content[div->i])
			|| data->current->original_content[div->i] == '_')
			div->i++;
	}
	else
	{
		if (data->current->original_content[0] == '?' && div->i == 0)
			div->i++;
		div->type1 = ENV;
		div->type2 = WORD;
		data->current = divide_lst(&data->tokens, data->current, div);
		return (1);
	}
	return (0);
}

void	dollar_parsing(t_data *data)
{
	t_div	div;
	char	*new_cont;

	new_cont = NULL;
	data->current = data->tokens;
	while (data->current)
	{
		div.i = 0;
		div.start = 0;
		while (data->current->original_content[div.i]
			&& data->current->type == ENV)
		{
			if (check_env(data, &div, new_cont))
				break ;
		}
		if (data->current)
			data->current = data->current->next;
	}
}

void	change_env_to_word(t_data *data, char *new_content)
{
	data->current = data->tokens;
	while (data->current)
	{
		if (data->current->type == ENV)
		{
			if (!ft_strcmp(data->current->original_content, "?"))
				new_content = get_value_from_env(data->env,
						data->current->original_content);
			else
				new_content = ft_strdup(get_value_from_env(data->env,
							data->current->original_content));
			free(data->current->original_content);
			data->current->original_content = new_content;
			if (!data->current->original_content)
				data->current = ft_lst_delone(&data->tokens, data->current);
			else
				data->current->type = WORD;
		}
		if (data->current)
			data->current = data->current->next;
		else
			break ;
	}
}

void	check_and_sort_env_token(t_data *data, char *new_cont)
{
	if (!data->current->next || (data->current->next
			&& data->current->next->type == SPACEO))
	{
		data->current = ft_lst_delone(&data->tokens, data->current);
		new_cont = ft_strjoin("$", data->current->original_content);
		free(data->current->original_content);
		data->current->original_content = new_cont;
		data->current->type = WORD;
		data->current = data->current->next;
	}
	else if (!data->current->next)
		data->current = data->current->next;
	else if (data->current->original_content[0] == '$')
		data->current = ft_lst_delone(&data->tokens, data->current);
	else if ((!ft_isalpha(data->current->original_content[0])
			&& !ft_isdigit(data->current->original_content[0])
			&& data->current->original_content[0] != '_'))
	{
		new_cont = ft_strjoin("$", data->current->original_content);
		free(data->current->original_content);
		data->current->original_content = new_cont;
	}
	if (data->current && data->current->original_content[0] != '$'
		&& data->current->type == WORD)
		data->current->type = ENV;
}

int	dollar_insertion(t_data *data)
{
	char	*new_cont;
	char	*new_content;

	new_cont = NULL;
	new_content = NULL;
	data->current = data->tokens;
	while (data->current)
	{
		if ((data->current->next && data->current->quotes != 1)
			&& data->current->original_content[0] == '$'
			&& (data->current->quotes == data->current->next->quotes))
		{
			check_and_sort_env_token(data, new_cont);
		}
		if (data->current)
			data->current = data->current->next;
	}
	dollar_parsing(data);
	change_env_to_word(data, new_content);
	return (EXIT_SUCCESS);
}
