/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/10/24 15:18:01 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_data(t_data *data)
{
    t_token *current = data->tokens;
    t_token *next;

    while (current != NULL) 
    {
        next = current->next;
        if (current->original_content)
        {
            free(current->original_content);
            current->original_content = NULL;
        }
        free(current);
        current = next;
    }
    data->tokens = NULL;
    free(data->input);
}

int fill_tokens(t_data *data, int i, int j, int quotes)
{
    t_token *token1;

    if(i - j <= 0)
        return(0);
    token1 = ft_lstnew(quotes);
    if(!token1)
        return(0);
    token1->original_content = ft_strndup(data->input, i, j);
    token1->type = data->type;
    if (!token1->original_content)
    {
        free(token1);
        return(0);
    }
    ft_lstadd_back(&data->tokens, token1);
    return(1);
}

int check_pipe_red_env(t_data *data)
{
    if(data->input[data->i] == '|')
    {
        data->i++;
        data->type = PIPE;
        fill_tokens(data, data->i, data->j, data->quotes_flag);
        return(1);
    }
    else if(data->input[data->i] == '>' || data->input[data->i] == '<')
    {
        data->i++;
        data->type = REDIR;
        fill_tokens(data, data->i, data->j, data->quotes_flag);
        return(1);
    }
    else if(data->input[data->i] == '$')
    {
        data->i++;
        fill_tokens(data, data->i, data->j, data->quotes_flag);
        return(1);
    }
    return(0);
}

int check_quotes(t_data *data)
{
    if(data->input[data->i] == '"')
    {
        data->i++;
        data->quotes_flag = DOUBLE;
        data->type = WORD;
        fill_tokens(data, data->i, data->j, data->quotes_flag);
        return(1);
    }
    else if(data->input[data->i] == '\'')
    {
        data->i++;
        data->quotes_flag = SINGLE;
        data->type = WORD;
        fill_tokens(data, data->i, data->j, data->quotes_flag);
        return(1);
    }
    return(0);
}

int check_space(t_data *data)
{
    while(data->input[data->i] && data->input[data->i] == ' ')
        data->i++;
    if(data->input[data->j] == ' ' && data->quotes_flag == 0)
    {
        data->j = data->i - 1;
        data->type = SPACE;
        fill_tokens(data, data->i, data->j, data->quotes_flag);
        return(1);
    }
    else if(data->input[data->j] == ' ' && data->quotes_flag != 0)
    {
        data->type = SPACE;
        fill_tokens(data, data->i, data->j, data->quotes_flag);
        return(1);
    }
    return(0);
}
