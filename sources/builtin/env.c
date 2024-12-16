/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:30:53 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/15 00:08:14 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env(t_env_export *env, char *key, char *value)
{
	t_env_export	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			if (!temp->value)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	return (EXIT_FAILURE);
}

char	*find_key(char *key_value)
{
	int		i;
	char	*key;

	if (!key_value)
		return (NULL);
	i = 0;
	while (key_value[i] && key_value[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (key_value[i] && key_value[i] != '=')
	{
		key[i] = key_value[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*find_value(char *key_value)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	if (!key_value)
		return (NULL);
	while (key_value[i] && key_value[i] != '=')
		i++;
	if (!key_value[i])
		return (NULL);
	value = (char *)malloc(sizeof(char) * (strlen(key_value) - i));
	if (!value)
		return (NULL);
	i++;
	while (key_value[i])
		value[j++] = key_value[i++];
	value[j] = '\0';
	return (value);
}

t_env_export	*init_env(char **env)
{
	int				i;
	t_env_export	*head;
	t_env_export	*current;
	t_env_export	*new_node;

	i = 0;
	head = NULL;
	current = NULL;
	while (env[i])
	{
		new_node = malloc(sizeof(t_env_export));
		if (!new_node)
			return (NULL);
		new_node->key = find_key(env[i]);
		new_node->value = find_value(env[i]);
		new_node->next = NULL;
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}

int	env(t_data *data)
{
	if (!data)
	{
		minishell_error("pwd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	print_list(data->env);
	return (EXIT_SUCCESS);
}
