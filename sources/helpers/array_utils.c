/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:07:05 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/21 20:47:13 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_list(struct t_env_export *env)
{
	struct t_env_export *temp;

	temp = env;
	if(!temp)
		return ;
	while(temp)
	{
		if(temp->key && temp->value)
		{
			write(STDOUT_FILENO, temp->key, ft_strlen(temp->key));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, temp->value, ft_strlen(temp->value));
			write(STDOUT_FILENO, "\n", 1);
			// printf("%s=%s\n", temp->key, temp->value);
		}
		temp = temp->next;
	}
}

void print_array(char **str)
{
	int i;

	i = 0;
    while (str[i])
    {
        printf("%s\n", str[i]);
        i++;
    }
}

void	*free_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str[i]);
	str[i] = NULL;
	free(str);
	str = NULL;
	return (NULL);
}

void sort_array(char **str)
{
    int i;
    int swapped;
    char *tmp;

    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        i = 0;
        while (str[i + 1])
        {
            if (ft_strcmp(str[i], str[i + 1]) > 0)
            {
                tmp = str[i];
                str[i] = str[i + 1];
                str[i + 1] = tmp;
                swapped = 1;
            }
            i++;
        }
    }
}


	// void sort_array(char **str)
	// {
	// 	int i;
	// 	char *tmp;

	// 	i = 0;
	// 	while(str[i + 1])
	// 	{
	// 		if(ft_strcmp(str[i], str[i + 1]) > 0)
	// 		{
	// 			tmp = str[i];
	// 			str[i] = str[i + 1];
	// 			str[i + 1] = tmp;
	// 			i = 0;
	// 		}
	// 		else
	// 			i++;
	// 	}
	// }

int count_array_len(char **str)
{
	int i;

	i = 0;
	if(!str)
		return (i);
	while(str[i])
		i++;

	return (i);
}
