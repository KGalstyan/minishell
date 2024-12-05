/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:16:00 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/05 20:41:44 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset_name(char *name)
{
	int	i;

	if (!name)
		return (EXIT_FAILURE);
	if (name[0] && !ft_isalpha(name[0]) && name[0] != '_')
		return (EXIT_FAILURE);
	i = 1;
	while (name[i])
	{
		if (name[i] != '_' && !ft_isalnum(name[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	ft_remove_var(struct t_env_export *prev, struct t_env_export *ptr)
{
	if (prev)
		prev->next = ptr->next;
	free_env_node(ptr);
}

char	*get_value_from_env(struct t_env_export *env, char *key)
{
	struct t_env_export	*temp;

	temp = env;
	if (!ft_strcmp(key, "?"))
		return (ft_itoa(get_g_exit_status()));
	while (temp)
	{
		if (temp->key && key && ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	is_builtin(char *cmd)
{
	if (cmd && (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
			|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
			|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
			|| ft_strcmp(cmd, "exit") == 0))
		return (1);
	return (0);
}
