/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:20:11 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/15 00:39:50 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(t_env_export *env, char *key)
{
	t_env_export	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	count_env_len(t_env_export *env)
{
	t_env_export	*temp;
	int				len;

	len = 0;
	temp = env;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

int	list_to_array_2(t_env_export *temp, char **matrix, int i)
{
	char	*tmp;

	if (!temp->value)
	{
		matrix[i] = ft_strdup(temp->key);
		if (!matrix[i])
			return (free_array(matrix), EXIT_FAILURE);
	}
	else
	{
		tmp = ft_strjoin(temp->key, "=");
		matrix[i] = ft_strjoin2(tmp, temp->value);
		free(tmp);
		if (!matrix[i])
			return (free_array(matrix), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	**list_to_array(t_env_export *env)
{
	char			**matrix;
	t_env_export	*temp;
	int				i;

	matrix = (char **)malloc(sizeof(char *) * (count_env_len(env) + 1));
	if (!matrix)
		return (NULL);
	i = 0;
	temp = env;
	while (temp)
	{
		if (list_to_array_2(temp, matrix, i) == EXIT_FAILURE)
			return (NULL);
		i++;
		temp = temp->next;
	}
	matrix[i] = NULL;
	return (matrix);
}

int	check_variable_name(char *name)
{
	int	i;

	if (!name)
		return (EXIT_FAILURE);
	if (name[0] && !ft_isalpha(name[0]) && name[0] != '_')
		return (EXIT_FAILURE);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (name[i] != '_' && !ft_isalnum(name[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

// t_env_export *new_node(char *env)
// {
//     t_env_export *new_node;

//     new_node = (t_env_export *)malloc(sizeof(t_env_export));
//     if(!new_node)
//         return (NULL);
//     new_node->key = find_key(env);
//     new_node->value = find_value(env);
//     new_node->next = NULL;
// }
