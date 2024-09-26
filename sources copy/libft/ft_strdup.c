/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:29:41 by vkostand          #+#    #+#             */
/*   Updated: 2024/09/21 18:56:45 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	str = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char    *ft_strndup(const char *s1, int n, int m)
{
    char    *str;
    int        i;
    int        j;

    if (m >= n)
        return (0);
    str = (char *)malloc((n - m + 1) * sizeof(char));
    if (str == NULL)
        return (0);
    i = m;
    j = 0;
    while (n > i)
    {
        str[j] = s1[i];
        i++;
        j++;
    }
    str[i] = '\0';
    return (str);
}
