/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:08:28 by kgalstya          #+#    #+#             */
/*   Updated: 2024/11/11 21:12:28 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_commands(t_data *data)
{
	int num;

	num = 1;
	data->current = data->tokens;
	while(data->current)
	{
		if(data->current->type == PIPE && (data->current->type == WORD))
			num++;
		data->current = data->current->next;
	}
	return(num);
}
void print_a(t_data *data)
{
    t_command *pr_cmd = data->commands;

	int i = 0;
    printf("🔵🔵🔵🔵🔵🔵🔵🔵🔵\n");
    while(pr_cmd)
    {
		i = 0;
		printf("	NAME  ->>>>>> %s\n", pr_cmd->name);
		while(pr_cmd->args[i])
		{
			printf("	ARGS ->>>>>> %s\n", pr_cmd->args[i]);
			i++;
		}
        pr_cmd = pr_cmd->next;
    }
}

void fill_commands(t_data *data)
{
	int len;
	t_token *tmp;

	len = 0;
	if(data->current->type == WORD)
		data->curr_cmd->name = ft_strdup(data->current->original_content);
	tmp = data->current;
	while(tmp && tmp->type == WORD)
	{
		len++;
		tmp = tmp->next;
	}
	if(len > 0)
	{
		data->curr_cmd->args = (char **)malloc(sizeof(char *) * (len + 1));
		if(!data->curr_cmd->args)
			return ;
		data->curr_cmd->args[len] = NULL;
	}
}

int handle_redir(t_data *data)
{
	data->current = data->tokens;
	data->curr_cmd = data->commands;
	while(data->current)
	{
		if(data->current->type == REDIR && ((!data->current->next) || data->current->next->type != WORD))
		{
			parse_error("newline");
			return(EXIT_FAILURE);
		}
		else if(data->current->type == REDIR && (data->current->next && data->current->next->type == WORD))
		{
			if(data->current->original_content[0] == '>')
			{
				data->current = ft_lst_delone(&data->tokens, data->current);
				data->curr_cmd->stdout = open(data->current->original_content, O_RDWR | O_CREAT);
			}
			else
			{
				data->current = ft_lst_delone(&data->tokens, data->current);
				data->curr_cmd->stdin = open(data->current->original_content, O_RDWR | O_CREAT);
			}
			data->current = ft_lst_delone(&data->tokens, data->current);
		}
		if(data->current)
			data->current = data->current->next;
		else
			break;
	}
	return(EXIT_SUCCESS);
}

int create_commands(t_data *data)
{
	int cmd_count;
	int i;
	int j;
	t_command *tmp;

	cmd_count = count_commands(data);
	i = 0;
	j = 0;
	data->commands = ft_lstnew_cmd();
	while(i < cmd_count - 1)
	{
		tmp = ft_lstnew_cmd();
    	if(!tmp)
        	return(MALLOC_ERR);
    	ft_lstadd_back_cmd(&data->commands, tmp);
		i++;
	}
	i = 0;
	data->curr_cmd = data->commands;
	data->current = data->tokens;
	while(data->current && i < cmd_count)
	{
		if(data->current->type == PIPE)
		{
			data->current = data->current->next;
			continue;
		}
		fill_commands(data);
		j = 0;
		while(data->current && data->current->type == WORD)
		{
			data->curr_cmd->args[j] = ft_strdup(data->current->original_content);
			data->current = data->current->next;
			j++;
		}
		data->curr_cmd->args[j] = NULL;
		if(data->current)
			data->current = data->current->next;
		data->curr_cmd = data->curr_cmd->next;
		i++;
	}
	data->curr_cmd = NULL;
	set_g_exit_status(handle_redir(data));
	print_a(data);
	return(0);
}

