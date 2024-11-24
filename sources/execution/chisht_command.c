/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chisht_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:10:00 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/22 20:12:44 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int count_commands(t_data *data)
// {
// 	int num;

// 	num = 1;
// 	data->current = data->tokens;
// 	while(data->current)
// 	{
// 		if(data->current->type == PIPE && (data->current->next && data->current->next->type == WORD))
// 			num++;
// 		data->current = data->current->next;
// 	}
// 	return(num);
// }

// void print_a(t_data *data)
// {
//     t_command *pr_cmd = data->commands;

// 	int i = 0;
//     while(pr_cmd)
//     {
// 		i = 0;
// 		if(pr_cmd->name)
// 			printf("	NAME  ->>>>>> %s\n", pr_cmd->name);
// 		if(pr_cmd->args)
// 		{
// 			while(pr_cmd->name)
// 			{
//     		printf("🔵🔵🔵🔵🔵🔵🔵🔵🔵\n");	
// 				printf("	ARGS ->>>>>> %s\n", pr_cmd->name);
// 				i++;
// 			}
// 		}
//         pr_cmd = pr_cmd->next;
//     }
// }

// // void fill_commands(t_data *data)
// // {
// // 	int len;
// // 	t_token *tmp;

// // 	len = 0;
// // 	if(data->current->type == WORD)
// // 		data->curr_cmd->name = ft_strdup(data->current->original_content);
// // 	tmp = data->current;
// // 	while(tmp && tmp->type == WORD)
// // 	{
// // 		len++;
// // 		tmp = tmp->next;
// // 	}
// // 	if(len > 0)
// // 	{
// // 		data->curr_cmd->args = (char **)malloc(sizeof(char *) * (len + 1));
// // 		if(!data->curr_cmd->args)
// // 			return ;
// // 		data->curr_cmd->args[len] = NULL;
// // 	}
// // }

// int count_command_len(t_token *token)
// {
// 	t_token *tmp;
// 	int len;

// 	tmp = token;
// 	len = 0;
// 	while(tmp && tmp->type != PIPE)
// 	{
// 		tmp = tmp->next;
// 		len++;
// 	}
// 	return (len);
// }

// char *find_command_name(t_token *token)
// {
// 	t_token *tmp;

// 	tmp = token;
// 	while(tmp)
// 	{
// 		if(tmp->type == WORD)
// 			return (tmp->original_content);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// char **token_to_command(t_data *data)
// {
// 	char **args;
// 	int len;
// 	int i;

// 	len = count_command_len(data->current);
// 	args = (char **)malloc(sizeof(char *) * (len + 1));
// 	if(!args)
// 		return (NULL);
// 	i = 0;
// 	while(i < len && data->current)
// 	{
// 		printf("content -> %s\n", data->current->original_content);
// 		args[i] = ft_strdup(data->current->original_content);
// 		if(!args[i])
// 			return (free_array(args), NULL);
// 		i++;
// 		data->current = data->current->next;
// 	}
// 	return (args);
// }

void free_one_command(t_data *data)
{
	data->curr_cmd = data->commands->next;
	free(data->commands->name);
	data->commands->name = NULL;
	free_array(data->commands->args);
	free(data->commands);
	data->commands = NULL;
	data->commands = data->curr_cmd;
}

// void free_commands(t_data *data)
// {
// 	t_command *tmp;
// 	while (data->commands)
// 	{
// 		tmp = data->commands->next;
// 		if(data->commands->name)
// 		{
// 			printf("name -> %s\n", data->commands->name);
// 			free(data->commands->name);
// 			data->commands->name = NULL;
// 		}
// 		if(data->commands->args)
// 			free_array(data->commands->args);
// 		data->commands = tmp;
// 	}
// }

void free_commands(t_data *data)
{
	data->curr_cmd = data->commands;	
	while (data->curr_cmd)
	{
		data->commands = data->commands->next;
		free(data->curr_cmd->name);
		data->curr_cmd->name = NULL;
		free_array(data->curr_cmd->args);
		free(data->curr_cmd);
		data->curr_cmd = NULL;
		data->curr_cmd = data->commands;
	}
}

// int fill_commands(t_data *data, int cmd_count)
// {
// 	int i;

// 	i = 0;
// 	data->curr_cmd = data->commands;
// 	data->current = data->tokens;
// 	while(i < cmd_count && data->curr_cmd)
// 	{
// 		data->curr_cmd->name = ft_strdup(find_command_name(data->current));
// 		data->curr_cmd->args = token_to_command(data);
// 		if(!data->curr_cmd->args)
// 			return (free_commands(data), MALLOC_ERR);
// 		data->current = data->current->next;
// 		i++;
// 		data->curr_cmd = data->curr_cmd->next;
// 	}
// 	printf("alooo\n");
// 	return (EXIT_SUCCESS);
// }

// int create_commands(t_data *data)
// {
// 	t_command *tmp;
// 	int cmd_count;
// 	int i;

// 	cmd_count = count_commands(data);
// 	i = 0;
// 	data->commands = ft_lstnew_cmd();
// 	if(!data->commands)
// 		return (MALLOC_ERR);
// 	while(i < cmd_count - 1)
// 	{
// 		tmp = ft_lstnew_cmd();
// 		if(!tmp)
//         	return(MALLOC_ERR);
// 		ft_lstadd_back_cmd(&data->commands, tmp);
// 		i++;
// 	}
// 	fill_commands(data, cmd_count);
// 	// print_a(data);
// 	return (EXIT_SUCCESS);
// }