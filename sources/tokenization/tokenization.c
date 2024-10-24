/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/10/24 15:18:15 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_tokens(t_data *data)
{
    data->i = 0;
    data->j = 0;
    data->quotes_flag = NONE;
    while(data->input[data->i])
    {
        data->quotes_flag = NONE;
        data->j = data->i;
        if(check_pipe_red_env(data))
            continue;
        else if(check_quotes(data))
            continue;
        else if(check_space(data))
            continue;
        while(data->input[data->i] && data->input[data->i] != ' ')
        {   
            if(data->input[data->i] == '<' || data->input[data->i] == '>')
                break;
            else if(data->input[data->i] == '$' || data->input[data->i] == '|')
                break;
            else if(data->input[data->i] == '"' || data->input[data->i] == '\'')
                break;
            data->i++;
        }
        data->type = WORD;
        fill_tokens(data, data->i, data->j, data->quotes_flag);
    }
}

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET_COLOR "\033[0m"

void print_data(t_data *data)
{
    t_token *pr_token = data->tokens;
    while(pr_token != NULL)
    {
        
        printf(RED "token --> " RESET_COLOR);
        printf(GREEN "[%s]" RESET_COLOR, pr_token->original_content);
        printf("  (%d) -->", pr_token->quotes);
        printf(YELLOW " type(%d) --> \n" RESET_COLOR, pr_token->type);
        pr_token = pr_token->next;
    }
    printf("⚪️⚪️⚪️⚪️⚪️⚪️⚪️⚪️⚪️⚪️\n");
}

void error_exit(t_data *data)
{
    printf("⛔️ INCORRECT INPUT\n");
    free_data(data);
    system("leaks minishell");
    exit(4);
}

void tokenization(t_data *data)
{
    create_tokens(data);
    allot_quotes_value(data);
    print_data(data);
    tokens_insertion(data);
}
void start_shell(t_data *data)
{
    while(1)
    {
        data->input = readline("Verishen: ");
        if (data->input)
            add_history(data->input);
        // print_data(data);
        tokenization(data);
        printf("✅ CORRECT INPUT\n");
        free_data(data);
        system("leaks minishell");
    }
}
