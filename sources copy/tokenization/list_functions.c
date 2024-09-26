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
    t_token *tmp;
    t_token *prev;

    prev = *lst;
    tmp = that_one->next;
    if (!del || !lst)
		return ;
    while(prev->next && (prev->next != that_one))
        prev = prev->next;
    prev->next = tmp;
    free(that_one->original_content);
    free(that_one);
}
