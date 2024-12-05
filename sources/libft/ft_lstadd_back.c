/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:00:08 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/24 21:25:56 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		new->next = NULL;
	}
}

void	ft_lstadd_back_cmd(t_command **lst, t_command *new)
{
	t_command	*add;

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
		new->next = NULL;
	}
}

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*add;

// 	add = *lst;
// 	if (!new)
// 		return ;
// 	if (!*lst)
// 		*lst = new;
// 	else
// 	{
// 		while (add->next != NULL)
// 			add = add->next;
// 		add->next = new;
// 	}
// }
