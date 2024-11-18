/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:51:12 by vkostand          #+#    #+#             */
/*   Updated: 2024/02/04 12:51:20 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			if (s[i + 1] == c || s[i + 1] == '\0')
				words += 1;
			i++;
		}
	}
	return (words);
}

static int	allocation(char **str, int j, int index)
{
	int	k;

	k = 0;
	str[index] = (char *)malloc(sizeof(char) * j + 1);
	if (!str[index])
	{
		while (k < index)
		{
			free(str[index]);
			k++;
		}
		free(str);
		return (1);
	}
	return (0);
}

static int	fill_string(char **str, char const *s, char c)
{
	int	len;
	int	index;

	index = 0;
	while (*s)
	{
		len = 0;
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			s++;
			len++;
		}
		if (len)
		{
			if (allocation(str, len + 1, index))
				return (1);
			ft_strlcpy(str[index], s - len, len + 1);
		}
		index++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	str = (char **)malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (NULL);
	str[words] = NULL;
	if (fill_string(str, s, c))
		return (NULL);
	return (str);
}
/*
int	main(void)
{
	printf("%s", *ft_split(",,,jan,", ','));
	return (0);
}*/
