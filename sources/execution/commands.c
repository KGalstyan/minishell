/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:08:28 by kgalstya          #+#    #+#             */
/*   Updated: 2024/12/03 20:18:12 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_data *data)
{
	int	num;

	num = 1;
	data->current = data->tokens;
	while (data->current)
	{
		if (data->current->type == PIPE)
			num++;
		data->current = data->current->next;
	}
	if (num > 100)
		return (set_g_exit_status(EXIT_FAILURE), minishell_error2("fork",
				"Resource temporarily unavailable", ""), -1);
	return (num);
}

void	fill_commands(t_data *data)
{
	int		len;
	t_token	*tmp;

	len = 0;
	if (data->current->type == WORD || data->current->type == SPACEO)
		data->curr_cmd->name = ft_strdup(data->current->original_content);
	tmp = data->current;
	while (tmp && tmp->type == WORD)
	{
		len++;
		tmp = tmp->next;
	}
	if (len > 0)
	{
		data->curr_cmd->args = (char **)malloc(sizeof(char *) * (len + 1));
		if (!data->curr_cmd->args)
			return ;
		data->curr_cmd->args[len] = NULL;
	}
}

int	create_commands_helper(t_data *data, int i, int j)
{
	while (data->current && i < data->pipe_count + 1)
	{
		if (data->current->type == PIPE)
		{
			data->current = data->current->next;
			continue ;
		}
		fill_commands(data);
		j = 0;
		while (data->current && data->current->type == WORD)
		{
			data->curr_cmd->args[j] = \
				ft_strdup(data->current->original_content);
			data->current = data->current->next;
			j++;
		}
		if (data->current)
			data->current = data->current->next;
		if (data->curr_cmd->next)
			data->curr_cmd = data->curr_cmd->next;
		else
			data->curr_cmd->next = NULL;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	create_commands(t_data *data)
{
	int			i;
	int			j;
	t_command	*tmp;

	data->pipe_count = count_commands(data) - 1;
	if (data->pipe_count < 0)
		return (EXIT_FAILURE);
	data->commands = ft_lstnew_cmd();
	i = 0;
	while (i++ < data->pipe_count)
	{
		tmp = ft_lstnew_cmd();
		if (!tmp)
			return (MALLOC_ERR);
		ft_lstadd_back_cmd(&data->commands, tmp);
	}
	if (handle_redir(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data->curr_cmd = data->commands;
	data->current = data->tokens;
	if (!data->current)
		return (EXIT_SUCCESS);
	i = 0;
	j = 0;
	return (create_commands_helper(data, i, j));
}
