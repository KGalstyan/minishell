/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/09/20 16:20:30 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return ((unsigned char const)s1[i] - (unsigned char const)s2[i]);
}

t_token	*ft_lstnew(int quotes)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->quotes = quotes;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*add;

	add = *lst;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (add->next != NULL)
			add = add->next;
		add->next = new;
	}
}

void fill_tokens(t_data *data, int i, int j, int quotes)
{
    t_token *token1;

    if(i - j == 0)
        return ;
    token1 = ft_lstnew(quotes);
    token1->original_content = ft_strndup(data->input, i, j);
    ft_lstadd_back(&data->tokens, token1);
}

void create_tokens(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(data->input[i])
    {
        j = i;
        if(data->input[i] == '"')
        {
            i++;
            while(data->input[i])
            {
                if(data->input[i] == '"')
                    break;
                i++;
            }
            if(!data->input[i])
                    exit(1);
            i++;
            fill_tokens(data, i, j, DOUBLE);
        }
        j = i;
        if(data->input[i] && data->input[i] == '\'')
        {
            i++;
            while(data->input[i])
            {
                if(data->input[i] == '\'')
                    break;
                i++;
            }
            if(!data->input[i])
                exit(1);
            i++;
            fill_tokens(data, i, j, SINGLE);
        }
        while(data->input[i] && ((data->input[i] == ' ' || data->input[i] == '\t')))
            i++;
        if(data->input[i - 1] == ' ')
        {
            j = i - 1;
            fill_tokens(data, i, j, NONE);
        }
        j = i;
        while(data->input[i] && ((!(data->input[i] == ' ' || data->input[i] == '\t')) && (!(data->input[i] == '"' || data->input[i] == '\''))))
            i++;
        fill_tokens(data, i, j, NONE);
    }
}

int is_command(char *content, t_token *token)
{
    if(ft_strcmp("env", content) || ft_strcmp("cd", content) || ft_strcmp("pwd", content))
    {
        token->type = COMMAND;
        return(1);
    }
    else if(ft_strcmp("export", content) || ft_strcmp("unset", content) || ft_strcmp("exit", content))
    {
        token->type = COMMAND;
        return(1);
    }
    return(0);
}


void sorting(t_data *data)
{
    int i;

    i = 0;
    while(data->tokens != NULL)
    {
        if(is_command(data->tokens->original_content, data->tokens))
        {
            if(data->tokens->next)
                data->tokens = data->tokens->next;
            else
                return;
            printf("🔴\n");
        }
        while(data->tokens && data->tokens->original_content[i])
        {
            if(data->tokens->original_content[i] == '$' && i == 0)
            {
                data->tokens->type = ENV;
                break;
            }
            else if(data->tokens->original_content[i] == ' ')
            {
                data->tokens->type = SPACE;
                break;
            }
            else if(data->tokens->original_content[i] == '<' || data->tokens->original_content[i] == '<')
            {
                data->tokens->type = REDIR;
                break;
            }
            else if(data->tokens->original_content[i] == '|')
            {
                data->tokens->type = PIPE;
                break;
            }
            i++;
        }
        data->tokens = data->tokens->next;
    }
}

void print_datas(t_data *data)
{
    while(!data->tokens)
    {
        printf("original token is -->    |%s|\n", data->tokens->original_content);
        printf("status is-->      %d\n", data->tokens->quotes);
        printf("type is ------------>>     %d\n", data->tokens->type);
        printf("⚪️⚪️⚪️⚪️⚪️⚪️⚪️⚪️⚪️\n");
        data->tokens = data->tokens->next;
    }
}
void start_shell(t_data *data)
{
    while(1)
    {
        data->input = readline("Verishen: ");
        create_tokens(data);
        //free_data(data);
        sorting(data);
        print_datas(data);
            //exit(2);
        //checking(data);
        //system("leaks minishell");
    }
}