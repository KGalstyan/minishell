/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_insertion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:10:02 by kgalstya          #+#    #+#             */
/*   Updated: 2024/10/30 21:38:57 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;
	size_t			mem;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	mem = ft_strlen(s + start);
	if (len < mem)
		mem = len;
	str = (char *)malloc((mem + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (s[i] != '\0' && j < len && !(start > (unsigned int)ft_strlen(s)))
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

// printf("🔵there will be hold this exit status\n");

void dollar_parsing(t_data *data)
{
    t_div div;
    char *new_cont;

    data->current = data->tokens;
    while(data->current)
    {
        div.i = 0;
        div.start = 0;
        while(data->current->original_content[div.i] && data->current->type == ENV)
        {
            if(ft_isalpha(data->current->original_content[div.i]) || ft_isdigit(data->current->original_content[div.i]) || data->current->original_content[div.i] == '_')
            {
                if(ft_isdigit(data->current->original_content[div.i]) && div.i == 0)
                {
                    div.i++;
                    new_cont = ft_substr(data->current->original_content, div.i, ft_strlen(data->current->original_content));
                    free(data->current->original_content);
                    data->current->original_content = new_cont;
                    break;
                }
                while(ft_isalpha(data->current->original_content[div.i]) || ft_isdigit(data->current->original_content[div.i]) || data->current->original_content[div.i] == '_')
                    div.i++;
            }
            else if(data->current->original_content[0] == '?' && div.i == 0)
            {
                div.i++;
                new_cont = ft_substr(data->current->original_content, div.i, ft_strlen(data->current->original_content));
                free(data->current->original_content);
                data->current->original_content = new_cont;
                printf("🔵there will be hold this exit status\n");
                break;
            }
            else
            {
                div.type1 = ENV;
                div.type2 = WORD;
                data->current = divide_lst(&data->tokens, data->current, &div);
                break;
            }
        }
        if(data->current)
            data->current = data->current->next;
    }
}

void dollar_insertion(t_data *data)
{
    char *new_cont;

    data->current = data->tokens;
    while(data->current)
    {
        if(data->current->quotes != 1 && data->current->original_content[0] == '$' && (data->current->quotes == data->current->next->quotes))
        {
            if(data->current->next && data->current->next->type == SPACE)
            {
                data->current = ft_lst_delone(&data->tokens, data->current);
                new_cont = ft_strjoin("$" , data->current->original_content);
                free(data->current->original_content);
                data->current->original_content = new_cont;
            }
            else if(!data->current->next)
                data->current = data->current->next;
            else if(data->current->original_content[0] == '$')
                data->current = ft_lst_delone(&data->tokens, data->current);
            else if((!ft_isalpha(data->current->original_content[0]) && !ft_isdigit(data->current->original_content[0]) && data->current->original_content[0] != '_'))
            {
                new_cont = ft_strjoin("$" , data->current->original_content);
                free(data->current->original_content);
                data->current->original_content = new_cont;
            }
            if(data->current)
                data->current->type = ENV;
        }
        if(data->current)
            data->current = data->current->next;
    }
    dollar_parsing(data);
    // change_key_to_value();
}

/*------------------------------ string_insertion -------------------------------------*/
void single_string_insertion(t_data *data)
{
    t_token *first;
    t_token *last;
    
    data->current = data->tokens;
    while (data->current)
    {
        if(data->current->quotes == 1)
        {
            first = data->current;
            last = data->current;
            while(data->current && data->current->quotes == 1)
            {
                if(data->current->quotes != 1 && (first != last))
                {
                    data->current = connect_lst_in_one(&data->tokens, first, last, WORD);
                    continue;
                }
                last = data->current;
                data->current = data->current->next;       
            }
            data->current = connect_lst_in_one(&data->tokens, first, last, WORD);
        }
        if(data->current && data->current->next)
            data->current = data->current->next;
        else
            return;
    }
}
void double_string_insertion(t_data *data)
{
    t_token *first;
    t_token *last;
    
    data->current = data->tokens;
    while (data->current)
    {
        if(data->current->quotes == 2)
        {
            first = data->current;
            last = data->current;
            while(data->current && data->current->quotes == 2)
            {
                if(data->current->quotes != 2 && (first != last))
                {
                    data->current = connect_lst_in_one(&data->tokens, first, last, WORD);
                    continue;
                }
                last = data->current;
                data->current = data->current->next;       
            }
            data->current = connect_lst_in_one(&data->tokens, first, last, WORD);
        }
        if(data->current && data->current->next)
            data->current = data->current->next;
        else
            return;
    }
}

void remove_brakets(t_data *data)
{
    data->current = data->tokens;
    while(data->current)
    {
        if(data->current->original_content[0] == '\'' && data->current->quotes == 1)
            data->current = ft_lst_delone(&data->tokens, data->current);
        else if(data->current->original_content[0] == '"' && data->current->quotes == 2)
            data->current = ft_lst_delone(&data->tokens, data->current);
        else
            data->current = data->current->next;
    }
}
/*------------------------------ string_insertion -------------------------------------*/

void redir_insertion(t_data *data)
{
    t_token *first;
    t_token *last;

    data->current = data->tokens;
    while(data->current)
    {
        first = data->current;
        if(data->current->quotes == 0 && (data->current->original_content[0] == '>' && data->current->next->original_content[0] == '>'))
        {
            if(data->current->next->quotes == 0)
            {
                last = data->current->next;
                data->current = connect_lst_in_one(&data->tokens, first, last, APPRED);
                if(!data->current)
                    error_exit(data);
                continue;
            }
        }
        else if(data->current->quotes == 0 && (data->current->original_content[0] == '>' || data->current->original_content[0] == '<'))
        {
            data->current->type = REDIR;
            if(!data->current->next)
                error_exit(data);
        }
        if(data->current)
            data->current = data->current->next;
        else
            return ;    
    }
}
void make_space_one(t_token *token)
{
    char *new_content;

    new_content = (char *)malloc(sizeof(char) * 2);
    new_content[0] = ' ';
    new_content[1] = '\0';
    free(token->original_content);
    token->original_content = new_content;
}

void connect_tokens(t_data *data)
{
    t_token *first;
    t_token *last;
    
    data->current = data->tokens;
    first = data->current;
    last = data->current;
    while(data->current)
    {   
        last = data->current;
        first = data->current;
        while(data->current && data->current->type != SPACE)
        {
            last = data->current;
            if(data->current->next)
                data->current = data->current->next;
            else break;
        }
        if(last != first)
            data->current = connect_lst_in_one(&data->tokens, first, last, WORD);
        else if(data->current->next)
            data->current = data->current->next;
        else 
            return ;
    }
}

void space_insertion(t_data *data)
{
    data->current = data->tokens;
    connect_tokens(data);
    while(data->current)
    {
        if(data->current->type == SPACE && data->current->quotes == 0)
            make_space_one(data->current);
        ///// poxel yst anhrajeshtutyan /////
        data->current = data->current->next;
    }
}

void tokens_insertion(t_data *data)
{
    remove_brakets(data);
    single_string_insertion(data);
    dollar_insertion(data);
    print_data(data);
    double_string_insertion(data);
    print_data(data);
    redir_insertion(data);
    space_insertion(data);
    print_data(data);
    // pipe_insertion(data);
    // heredoc_insertion(data);
}
