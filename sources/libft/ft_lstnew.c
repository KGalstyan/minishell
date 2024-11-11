/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:58:30 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/11 17:48:56 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_command	*ft_lstnew_cmd(void)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);;
	new->next = NULL;
	return (new);
}

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*new;

// 	new = (t_list *)malloc(sizeof(t_list));
// 	if (!new)
// 		return (NULL);
// 	new->content = content;
// 	new->next = NULL;
// 	return (new);
// }
