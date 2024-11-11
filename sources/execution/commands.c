/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:08:28 by kgalstya          #+#    #+#             */
/*   Updated: 2024/11/11 16:33:49 by kgalstya         ###   ########.fr       */
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
		if(data->current->type == PIPE)
			num++;
		data->current = data->current->next;
	}
	return(num);
}

void fill_commands(t_data *data)
{
	int len;
	t_token *tmp;

	len = 0;
	if(data->current->type == WORD)
	{
		data->curr_cmd->name = ft_strdup(data->current->original_content);
		data->current = data->current->next;
	}
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

void print_a(t_data *data)
{
    t_command *pr_cmd = data->commands;

	printf("%s\n", pr_cmd->name);
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

int


int create_commands(t_data *data)
{
	int cmd_count;
	int i;
	int j;

	cmd_count = count_commands(data);
	i = 0;
	j = 0;
	data->commands = (t_command *)malloc(sizeof(t_command) * cmd_count);
	if(!data->commands)
		return(MALLOC_ERR);
	while(i < cmd_count - 1)
	{
        data->curr_cmd = (t_command *)malloc(sizeof(t_command));
        if (!data->curr_cmd->next)
            return MALLOC_ERR;
        data->curr_cmd = data->curr_cmd->next;
		i++;
	}
	i = 0;
	data->curr_cmd = data->commands;
	data->current = data->tokens;
	while(i < cmd_count)
	{
		while(data->current && data->current->type != PIPE)
		{
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
		}
		data->curr_cmd = data->curr_cmd->next;
		i++;
	}
	print_a(data);
	return(0);
}

