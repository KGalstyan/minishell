/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/09/26 21:00:08 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_lst_delone(t_token **lst, t_token *that_one)
{
    //t_token *tmp;
    t_token *prev;

    if (!that_one || !lst || !*lst)
        return;
    else
        prev = *lst;
    //tmp = that_one->next;
    while(prev->next && (prev->next != that_one))
        prev = prev->next;
      
    //prev->next = tmp;
    if (that_one->original_content)
        free(that_one->original_content);
    free(that_one);
}

void connect_lst_in_one(t_token **lst, t_token *first, t_token *last)
{
  t_token *new;
  t_token *ptr;
  t_token *tmp;
  char *new_origcont;
  
  if(first == last)
    return ;
  if (!first || !lst || !*lst || !last)
    return;
  new = ft_lstnew(first->quotes);
  ptr = *lst;
  //new_origcont = NULL;
  while(ptr && (ptr != first))
  {
    ptr->next = new;
    ptr = ptr->next;
  }
  tmp = last->next;
  while(ptr && (ptr != last->next))
  {
    new_origcont = ft_strjoin(new_origcont, ptr->content);
    new->quotes = ptr->quotes;
    free(ptr->original_content)
    free(ptr);
    ptr = ptr->next;
  }
  new->original_content = new_origcont;
  new->next = tmp;
}

