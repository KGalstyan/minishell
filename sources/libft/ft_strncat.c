/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:42:34 by vkostand          #+#    #+#             */
/*   Updated: 2024/10/31 15:42:55 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strncat(const char *str, int start, int end)
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
