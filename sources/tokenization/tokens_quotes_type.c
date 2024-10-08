/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_quotes_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:04:04 by kgalstya          #+#    #+#             */
/*   Updated: 2024/10/06 18:43:03 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_quotes_close(t_data *data)
{
    int i;
    
    i = 0;
    while(data->input[i])
    {
        if(data->input[i] && data->input[i] == '\'')
        {
            i++;
            while(data->input[i] && data->input[i] != '\'')
                i++;
        }
        else if(data->input[i] && data->input[i] == '"')
        {
            i++;
            while(data->input[i] && data->input[i] != '"')
                i++;
        }
        if(!data->input[i])
            error_exit(data);
        i++;
    }
}

static int allot_double_quotes_value(t_data *data)
{
    int i;

    i = 0;
    if(data->current->next)
        data->current = data->current->next;
    if(data->current && data->current->original_content[i] == '"')
    {
        data->current->quotes = DOUBLE;
        data->current = data->current->next;
        return(1);
    }
    while(data->current && data->current->original_content[i] != '"')
    {
        data->current->quotes = DOUBLE;
        data->current = data->current->next;
    }
    if(data->current && data->current->original_content[i] == '"')
    {
        data->current->quotes = DOUBLE;
        data->current = data->current->next;
    }
    return(1);
}

static int allot_single_quotes_value(t_data *data)
{
    int i;

    i = 0;
    if(data->current->next)
        data->current = data->current->next;
    if(data->current && data->current->original_content[i] == '\'')
    {
        data->current->quotes = SINGLE;
        data->current = data->current->next;
        return(1);
    }
    while(data->current && data->current->original_content[i] != '\'')
    {
        data->current->quotes = SINGLE;
        data->current = data->current->next;
    }
    if(data->current && data->current->original_content[i] == '\'')
    {
        data->current->quotes = SINGLE;
        data->current = data->current->next;
    }
    return(1);
}
void allot_quotes_value(t_data *data)
{
    int i;

    i = 0;
    data->current = data->tokens;
    check_quotes_close(data);
    while(data->current)
    {
        if(data->current->original_content[i] == '"')
            allot_double_quotes_value(data);
        else if(data->current->original_content[i] == '\'')
            allot_single_quotes_value(data);
        else
        {
            data->current->quotes = NONE;
            data->current = data->current->next;
        }
    }
    data->current = NULL;
}
