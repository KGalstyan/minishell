/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:08:28 by kgalstya          #+#    #+#             */
/*   Updated: 2024/11/11 18:42:44 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_remove_list(t_token *prev, t_token *ptr)
{
        if (prev)
          prev->next = ptr->next;
		if(ptr->original_content)
        	free(ptr->original_content);
        free(ptr);
}
t_token *ft_lst_delone(t_token **lst, t_token *that_one)
{
    t_token *ptr;
    t_token *prev;

    if (!lst || !*lst || !that_one)
        return NULL;
    if (*lst == that_one)
    {
        ptr = (*lst)->next;
        free((*lst)->original_content);
        free(*lst);
        *lst = ptr;
        return (ptr);
    }
    prev = NULL;
    ptr = *lst;
    while (ptr && ptr != that_one)
    {
        prev = ptr;
        ptr = ptr->next;
    }
    if (ptr == that_one)
        ft_remove_list(prev, ptr);
    return(prev->next);
}

t_token *connect_lst_in_one(t_token **lst, t_token *first, t_token *last, int type)
{
    t_token *new;
    t_token *ptr;
    t_token *tmp;
    char *new_origcont;
    char *temp_origcont;
    t_token *to_free;

    if (!first || !lst || !*lst || !last)
      return (NULL);
    if(first == last)
        return (first);
    new = malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->quotes = first->quotes;
    ptr = first;
    tmp = last->next;
    new_origcont = ft_strdup("");
    if (!new_origcont)
    {
        free(new);
        return NULL;
    }
    while (ptr && ptr != tmp)
    {
        if (!ptr->original_content)
        {
            free(new_origcont);
            free(new);
            return NULL;
        }
        temp_origcont = ft_strjoin(new_origcont, ptr->original_content);
        if (!temp_origcont)
        {
            free(new_origcont);
            free(new);
            return NULL;
        }
        free(new_origcont);
        new_origcont = temp_origcont;
        ptr = ptr->next;
    }
    new->original_content = new_origcont;
    new->type = type;
    new->next = tmp;
    if (first == *lst)
        *lst = new;
    else
    {
        ptr = *lst;
        while (ptr && ptr->next != first)
            ptr = ptr->next;
        if (ptr)
            ptr->next = new;
    }
    ptr = first;
    while (ptr && ptr != tmp)
    {
        to_free = ptr;
        ptr = ptr->next;
        free(to_free->original_content);
        free(to_free);
    }
    return tmp;
}

static int check_new_list(t_token *new1, t_token *new2, t_token *selected, t_div *div)
{
    if (!new1 || !new2)
    {
        free(new1);
        free(new2);
        return (0);
    }
    new1->quotes = selected->quotes;
    new2->quotes = selected->quotes;
    new1->type = div->type1;
    new2->type = div->type2;
    new1->original_content = ft_strncat(selected->original_content, div->start, div->i - 1);
    new2->original_content = ft_strncat(selected->original_content,div->i, ft_strlen(selected->original_content));
    if (!new1->original_content || !new2->original_content)
    {
        free(new1->original_content);
        free(new2->original_content);
        free(new1);
        free(new2);
        return (0);
    }
    return(1);
}

t_token *divide_lst(t_token **lst, t_token *selected, t_div *div)
{
    t_token *ptr;
    t_token *new1;
    t_token *new2;

    if (!lst || !*lst || !selected)
        return NULL;
    new1 = malloc(sizeof(t_token));
    new2 = malloc(sizeof(t_token));
    if(!check_new_list(new1, new2, selected, div))
        return(NULL);
    ptr = *lst;
    if (ptr == selected)
        *lst = new1;
    else {
        while (ptr && ptr->next != selected)
            ptr = ptr->next;
        if (ptr)
            ptr->next = new1;
    }
    new1->next = new2;
    new2->next = selected->next;
    free(selected->original_content);
    free(selected);
    return (new2->next);
}


