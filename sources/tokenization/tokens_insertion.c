/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_insertion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/09/26 20:33:10 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void ft_lst_insert(t_tokens **lst, t_token *first, t_token *last)
// {
// }

// void ft_lst_join(t_tokens **lst, t_token *first, t_token *last)
// {
//     t_token *tmp;

//     if(!first || !last)
//         return ;
//     if(!lst || !(*lst))
//         return ;
//     while()
// }

static void dollar_insertion(t_data *data)
{
    t_token *first;
    t_token *last;

    data->current = data->tokens;
    while(data->current)
    {
        if(data->current->original_content[0] == '$' && data->current->quotes != 1)
        {
            ft_lst_delone(&data->tokens, data->current);
            data->current = data->current->next;
            data->current->type = ENV;
        }
        data->current = data->current->next;
    }
}

void single_string_insertion(t_data *data)
{
    data->current = data->tokens;
    while(data->current)
    {
        if(data->current->quotes == SINGLE)
            first = data->current;
        while(data->current && data->current->quotes == SINGLE)
        {
            last = data->current
            data->current = data->current->next;
        }
        connect_lst_in_one(&data->tokens, first, last, WORD);
        data->current = data->current->next;
    }
}

void pipe_insertion(t_data *data)
{
    data->current = data->tokens;
    while(data->current)
    {
    }
}

void tokens_insertion(t_data *data)
{
    single_string_insertion(data);
    dollar_insertion(data);
    pipe_insertion(data);
    
}