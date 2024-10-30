/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/10/28 13:14:29 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return ((unsigned char const)s1[i] - (unsigned char const)s2[i]);
}

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
