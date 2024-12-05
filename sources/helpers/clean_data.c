/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:25:46 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/24 21:21:28 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void free_data(t_data data)
// {
//     t_token current = data->tokens;
//     t_token *next;

//     while (current != NULL)
//     {
//         next = current->next;
//         if (current->original_content)
//         {
//             free(current->original_content);
//             current->original_content = NULL;
//         }
//         free(current);
//         current = next;
//     }
//     data->tokens = NULL;
//     free(data->input);
// }

void	free_env_export(struct t_env_export *env_export)
{
	struct t_env_export	*temp;

	while (env_export)
	{
		temp = env_export->next;
		if (env_export->key)
		{
			free(env_export->key);
			env_export->key = NULL;
		}
		if (env_export->value)
		{
			free(env_export->value);
			env_export->value = NULL;
		}
		free(env_export);
		env_export = temp;
	}
	free(env_export);
	env_export = NULL;
}

void	free_env(t_data *data)
{
	struct t_env_export	*temp;

	while (data->env)
	{
		temp = data->env->next;
		if (data->env->key)
		{
			free(data->env->key);
			data->env->key = NULL;
		}
		if (data->env->value)
		{
			free(data->env->value);
			data->env->value = NULL;
		}
		free(data->env);
		data->env = temp;
	}
	free(data->env);
	data->env = NULL;
}

void	clean_data(t_data *data)
{
	(void)data;
	free_env_export(data->env);
	data->env = NULL;
	free_env_export(data->export);
	data->export = NULL;
}

void	free_env_node(struct t_env_export *node)
{
	if (node->key)
	{
		free(node->key);
		node->key = NULL;
	}
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	free(node);
	node = NULL;
}
