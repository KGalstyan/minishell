/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:54:07 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/14 23:41:04 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i;
	int		n;
	char	*res;

	if (!s2)
		return (ft_strdup(s1));
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

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*s;
// 	int		i;
// 	int		j;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	s = (char *)malloc(sizeof(char const)
// 			* (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (s == NULL)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1[i] != '\0')
// 	{
// 		s[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j] != '\0')
// 	{
// 		s[i + j] = s2[j];
// 		j++;
// 	}
// 	s[i + j] = '\0';
// 	free((void *)s2);
// 	return (s);
// }
