/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/09/20 15:04:41 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0') && i < n - 1)
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
        j = i;
        while(data->input[i] && ((!(data->input[i] == ' ' || data->input[i] == '\t')) && (!(data->input[i] == '"' || data->input[i] == '\''))))
            i++;
        fill_tokens(data, i, j, NONE);
    }
    // while(data->tokens != NULL)
    // {
    //     printf("original token is --> |%s| \n", data->tokens->original_content);
    //     printf("status is %d\n", data->tokens->quotes);
    //     data->tokens = data->tokens->next;
    // }
}

int is_command(t_data *data)
{
}
int is_env(t_data *data)
{
}
void sorting(t_data *data)
{
}

void start_shell(t_data *data)
{
    while(1)
    {
        data->input = readline("Verishen: ");
        create_tokens(data);
        //free_data(data);
        sorting(data);
        //system("leaks minishell");
    }
}