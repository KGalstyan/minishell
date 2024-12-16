/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:32:07 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/14 23:45:08 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_export	*add_oldpwd(t_env_export *env)
{
	t_env_export	*oldpwd;
	t_env_export	*temp;

	oldpwd = NULL;
	temp = env;
	while (temp && ft_strcmp(temp->key, "OLDPWD") != 0)
		temp = temp->next;
	if (!temp)
	{
		oldpwd = (t_env_export *)malloc(sizeof(t_env_export));
		if (!oldpwd)
			return (NULL);
		oldpwd->key = ft_strdup("OLDPWD");
		oldpwd->value = NULL;
		oldpwd->next = env;
		return (oldpwd);
	}
	else
		return (env);
}

t_env_export	*add_node(t_env_export *export, char *key, char *value)
{
	t_env_export	*node;

	if (update_env(export, key, value) == EXIT_SUCCESS)
		return (export);
	if (!key || !export)
		return (NULL);
	node = (t_env_export *)malloc(sizeof(t_env_export));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = export;
	return (node);
}

int	update_variable(t_env_export *export, char *key, char *value)
{
	t_env_export	*temp;

	temp = export;
	while (temp)
	{
		if (ft_strcmp(key, temp->key) == 0)
		{
			if (value)
			{
				free(temp->value);
				temp->value = value;
			}
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	return (EXIT_FAILURE);
}

t_env_export	*set_variable(t_env_export *export, char *var)
{
	t_env_export	*new;
	char			*key;
	char			*value;

	key = find_key(var);
	value = find_value(var);
	if (update_variable(export, key, value) == EXIT_SUCCESS)
		return (free(key), export);
	if (ft_strchr(var, '=') == 0)
	{
		new = add_node(export, var, NULL);
		return (free(key), free(value), new);
	}
	new = add_node(export, key, value);
	free(key);
	free(value);
	return (new);
}

int	export(t_data *data, char **args)
{
	int	i;
	int	status;

	status = 0;
	if (!data->export || !args)
		return (EXIT_FAILURE);
	if (args[0] && !args[1])
		return (print_export(data->export), EXIT_SUCCESS);
	i = 1;
	while (args[i])
	{
		if (check_variable_name(args[i]) == EXIT_SUCCESS)
		{
			data->export = merge(set_variable(data->export, args[i]),
					ft_strcmp);
			data->env = set_variable(data->env, args[i]);
		}
		else
		{
			status = 1;
			minishell_error("export", args[i], "not a valid identifier");
		}
		i++;
	}
	return (status);
}
