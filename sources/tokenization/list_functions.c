/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/10/09 19:45:10 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		n;
	char	*res;

	if (!s2)
		return (NULL);
	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	i = 0;
	n = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[n] != '\0')
	{
		res[i] = s2[n];
		n++;
		i++;
	}
	res[i] = '\0';
	return (res);
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
        return (NULL);
    }
    prev = NULL;
    ptr = *lst;
    while (ptr && ptr != that_one) 
    {
        prev = ptr;
        ptr = ptr->next;
    }
    if (ptr == that_one) 
    {
        if (prev)
          prev->next = ptr->next;
        free(ptr->original_content);
        free(ptr);
    }
    return *lst;
}


t_token *connect_lst_in_one(t_token **lst, t_token *first, t_token *last, int type)
{
    t_token *new;
    t_token *ptr;
    t_token *tmp;
    char *new_origcont;
    char *temp_origcont;
    t_token *to_free;

    if (!first || !lst || !*lst || !last || first == last)
      return (NULL);
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
    return new->next;
}


static char *ft_strncat(const char *str, int start, int end)
{
    int length;
    char *new_str;
    int n;
    
    if (start > end || start < 0 || end < 0)
        return NULL;
    length = end - start + 1;
    n = 0;
    new_str = (char *)malloc(length + 1);
    if (!new_str)
        return NULL;
    while(n < length)
    {
        new_str[n] = str[start + n];
        n++;
    }
    new_str[length] = '\0';
    return new_str;
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

