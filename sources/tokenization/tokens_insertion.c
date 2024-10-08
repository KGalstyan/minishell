// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   tokens_insertion.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
// /*   Updated: 2024/10/06 19:00:19 by kgalstya         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "minishell.h"

// void dollar_insertion(t_data *data)
// {
//     t_token *first;
//     t_token *last;
    
//     data->current = data->tokens;
//     while(data->current)
//     {
//         while(data->current && data->current->quotes == 0)
//         {
//             if(data->current->original_content[0] == '$')
//             {
//                 data->current = ft_lst_delone(&data->tokens, data->current);
//                 if(!data->current)
//                     return ;
//                 data->current->type = ENV;
//             }
//             data->current = data->current->next;
//         }
//         if(data->current)
//             data->current = data->current->next;
//     }
// }
int	ft_isdigit(int b)
{
	if (b >= 48 && b <= 57)
		return (1);
	else
		return (0);
}

int	ft_isalpha(int a)
{
	if ((a < 'A' || a > 'z') || (a > 'Z' && a < 'a'))
		return (0);
	else
		return (1);
}


void dollar_parsing(t_data *data)
{
    t_div div;

    div.i = 0;
    div.j = 0;
    data->current = data->tokens;
    while(data->current)
    {
        div.i = 0;
        div.j = 0;
        while(data->current->original_content[div.i] && data->current->type == ENV)
        {
            if(ft_isalpha(data->current->original_content[div.i]) || ft_isdigit(data->current->original_content[div.i]) || data->current->original_content[div.i] == '_')
            {
                div.j = div.i;
                while(ft_isalpha(data->current->original_content[div.i]) || ft_isdigit(data->current->original_content[div.i]) || data->current->original_content[div.i] == '_')
                    div.i++;
            }
            else
            {
                data->current = divide_lst(&data->tokens, data->current, &div);
                div.i++;
            }
        }
        if(data->current)
            data->current = data->current->next;
    }
}

void dollar_insertion(t_data *data)
{
    data->current = data->tokens;
    while(data->current)
    {
        if(data->current->quotes != 1 && data->current->original_content[0] == '$')
        {
            if(data->current->next)
                data->current->next->type = ENV;
            data->current = ft_lst_delone(&data->tokens, data->current);
            continue;
        }
        data->current = data->current->next;
    }
    dollar_parsing(data);
}

void single_string_insertion(t_data *data)
{
    t_token *first;
    t_token *last;
    data->current = data->tokens;

    while (data->current)
    {
        if(data->current->original_content[0] == '\'' && data->current->quotes == 1)
            data->current = ft_lst_delone(&data->tokens, data->current);
        if(!data->current)
            return ;
        first = data->current;
        while(data->current && data->current->quotes == 1)
        {
            if(data->current->original_content[0] == '\'')
            {
                data->current = connect_lst_in_one(&data->tokens, first, last, WORD);
                break;
            }
            last = data->current;
            data->current = data->current->next;
        }
        if(data->current && (data->current->original_content[0] == '\'' && data->current->quotes == 1))
            data->current = ft_lst_delone(&data->tokens, data->current);
        if(data->current)
            data->current = data->current->next;
        else
            return ;
    }
}
void double_string_insertion(t_data *data)
{
    t_token *first;
    t_token *last;
    data->current = data->tokens;

    while (data->current)
    {
        if(data->current->original_content[0] == '"' && data->current->quotes == 2)
            data->current = ft_lst_delone(&data->tokens, data->current);
        if(!data->current)
            return ;
        first = data->current;
        while(data->current && data->current->quotes == 2)
        {
            if(data->current->original_content[0] == '"')
            {
                data->current = connect_lst_in_one(&data->tokens, first, last, WORD);
                break;
            }
            last = data->current;
            data->current = data->current->next;
        }
        if(data->current && (data->current->original_content[0] == '"' && data->current->quotes == 2))
            data->current = ft_lst_delone(&data->tokens, data->current);
        if(data->current)
            data->current = data->current->next;
        else
            return ;
    }
}

void tokens_insertion(t_data *data)
{
    single_string_insertion(data);
    dollar_insertion(data);
    double_string_insertion(data);
    print_data(data);
    // free_data(data);
    //pipe_insertion(data); 
}
