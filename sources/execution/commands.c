/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:08:28 by kgalstya          #+#    #+#             */
/*   Updated: 2024/11/14 17:29:29 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_commands(t_data *data)
{
	int num;

	num = 1;
	data->current = data->tokens;
	if(data->current && data->current->type == PIPE)
		data->current = data->current->next;
	while(data->current)
	{
		if(data->current && data->current->next && data->current->type == REDIR)
		{
			data->current = data->current->next;
			data->current = data->current->next;
			if(data->current && data->current->type == PIPE)
				data->current = data->current->next;
			continue;
		}
		else if(data->current && data->current->type == PIPE) //&& (data->current->type == WORD))
		{
			num++;
			data->current = data->current->next;
		}
		else
			data->current = data->current->next;
	}
	return(num);
}
void print_a(t_data *data __attribute__((unused)))
{
    t_command *pr_cmd = data->commands;

	int i = 0;
    printf("🔵🔵🔵🔵🔵🔵🔵🔵🔵\n");
    while(pr_cmd)
    {
		i = 0;
		if(pr_cmd->name)
			printf("	NAME  ->>>>>> %s\n", pr_cmd->name);
		if(!pr_cmd->args)
		{
			pr_cmd = pr_cmd->next;
			continue;
		}
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

int open_file_and_remove_token(t_data *data)
{
	if(data->current->original_content[0] == '>')
	{
		data->current = ft_lst_delone(&data->tokens, data->current);
		data->curr_cmd->stdout = open(data->current->original_content, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if(data->curr_cmd->stdout < 0)
		{
			printf("minishell: %s: %s\n", data->current->original_content, (strerror(errno)));
			set_g_exit_status(EXIT_FAILURE);
			return(EXIT_FAILURE);
		}
	}
	else
	{
		data->current = ft_lst_delone(&data->tokens, data->current);
		data->curr_cmd->stdin = open(data->current->original_content, O_RDONLY);
		if(data->curr_cmd->stdin < 0)
		{
			printf("minishell: %s: %s\n", data->current->original_content, (strerror(errno)));
			set_g_exit_status(EXIT_FAILURE);
			return(EXIT_FAILURE);
		}
	}
	data->current = ft_lst_delone(&data->tokens, data->current);
	return(EXIT_SUCCESS);
}

int handle_redir(t_data *data)
{
	data->current = data->tokens;
	data->curr_cmd = data->commands;
	while(data->current)
	{
		if(data->current->type == REDIR && data->current->next && (data->current->next->type == REDIR || data->current->next->type == HEREDOC))
		{
			parse_error(">>");
			set_g_exit_status(EXIT_FAILURE);
			return(EXIT_FAILURE);
		}
		else if(data->current->type == REDIR && ((!data->current->next) || data->current->next->type != WORD))
		{
			parse_error("newline");
			set_g_exit_status(EXIT_FAILURE);
			return(EXIT_FAILURE);
		}
		else if(data->current->type == REDIR && (data->current->next && data->current->next->type == WORD))
		{
			if(open_file_and_remove_token(data))
				return(EXIT_FAILURE);
		}
		else if(data->current)
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
	// printf("========= %d \n", cmd_count);
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
	if(get_g_exit_status(handle_redir(data)))
		return(EXIT_FAILURE);
	print_data(data);
	i = 0;
	data->curr_cmd = data->commands;
	data->current = data->tokens;
	if(!data->current)
		return(0);
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
		if(data->curr_cmd)
			data->curr_cmd = data->curr_cmd->next;
		else
			data->curr_cmd->next = NULL;
		i++;
	}
	if(!data->curr_cmd)
		data->curr_cmd = NULL;
	print_a(data);
	return(0);
}

