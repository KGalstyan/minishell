/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_lists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:54:08 by kgalstya          #+#    #+#             */
/*   Updated: 2024/11/19 21:39:04 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void create_new_token(t_new_token *new_tok, t_token **lst, t_token *first, int type)
{
    new_tok->new->original_content = new_tok->new_origcont;
    new_tok->new->type = type;
    new_tok->new->next = new_tok->tmp;
    if (first == *lst)
    	*lst = new_tok->new;
    else
    {
        new_tok->ptr = *lst;
        while (new_tok->ptr && new_tok->ptr->next != first)
            new_tok->ptr = new_tok->ptr->next;
        if (new_tok->ptr)
            new_tok->ptr->next = new_tok->new;
    }
    new_tok->ptr = first;
    while (new_tok->ptr && new_tok->ptr != new_tok->tmp)
    {
        new_tok->to_free = new_tok->ptr;
        new_tok->ptr = new_tok->ptr->next;
        free(new_tok->to_free->original_content);
        free(new_tok->to_free);
    }
}

int check_new_token(t_new_token *new_tok)
{
	while (new_tok->ptr && new_tok->ptr != new_tok->tmp)
    {
        if (!new_tok->ptr->original_content)
        {
            free(new_tok->new_origcont);
            free(new_tok->new);
            return(1);
        }
        new_tok->tmp_origcont = ft_strjoin(new_tok->new_origcont, new_tok->ptr->original_content);
        if (!new_tok->tmp_origcont)
        {
            free(new_tok->new_origcont);
            free(new_tok->new);
            return(1);
        }
        free(new_tok->new_origcont);
        new_tok->new_origcont = new_tok->tmp_origcont;
        new_tok->ptr = new_tok->ptr->next;
    }
	return(0);
}

t_token *connect_lst_in_one(t_token **lst, t_token *first, t_token *last, int type)
{
    t_new_token new_tok;

    if (!first || !lst || !*lst || !last)
      return (NULL);
    if(first == last)
    {
        first->type = type;
        return (first);
    }
    new_tok.new = malloc(sizeof(t_token));
    if (!new_tok.new)
        return (NULL);
    new_tok.new->quotes = first->quotes;
    new_tok.ptr = first;
    new_tok.tmp = last->next;
    new_tok.new_origcont = ft_strdup("");
    if (!new_tok.new_origcont)
    {
        free(new_tok.new);
        return NULL;
    }
	if(check_new_token(&new_tok))
		return(NULL);
	create_new_token(&new_tok, lst, first, type);
	return(new_tok.new);
}
