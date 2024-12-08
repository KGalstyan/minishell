/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:35:30 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/07 15:56:30 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_export	*mid_point(t_env_export *head)
{
	t_env_export	*mid;
	t_env_export	*end;

	mid = head;
	end = head->next;
	while (end && end->next)
	{
		mid = mid->next;
		end = end->next->next;
	}
	return (mid);
}

t_env_export	*merge_sorted_list(t_env_export *left,
		t_env_export *right, int (*cmp)())
{
	t_env_export	*sorted_list;
	t_env_export	temp;

	sorted_list = &temp;
	while (left && right)
	{
		if ((*cmp)(left->key, right->key) < 0)
		{
			sorted_list->next = left;
			left = left->next;
		}
		else if ((*cmp)(left->key, right->key) > 0)
		{
			sorted_list->next = right;
			right = right->next;
		}
		sorted_list = sorted_list->next;
	}
	if (left)
		sorted_list->next = left;
	else if (right)
		sorted_list->next = right;
	return (temp.next);
}

t_env_export	*merge(t_env_export *begin, int (*cmp)())
{
	t_env_export	*left;
	t_env_export	*right;
	t_env_export	*mid;

	if (!begin || !begin->next)
		return (begin);
	mid = mid_point(begin);
	left = begin;
	right = mid->next;
	mid->next = NULL;
	left = merge(left, cmp);
	right = merge(right, cmp);
	return (merge_sorted_list(left, right, cmp));
}
