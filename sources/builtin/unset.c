/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:33:28 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/13 15:04:32 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_export	*ft_lst_delvar(t_env_export **lst,
		t_env_export *that_one)
{
	t_env_export	*ptr;
	t_env_export	*prev;

	if (!lst || !*lst || !that_one)
		return (NULL);
	if (*lst == that_one)
	{
		ptr = (*lst)->next;
		free_env_node(*lst);
		*lst = ptr;
		return (ptr);
	}
	prev = NULL;
	ptr = *lst;
	while (ptr && ptr != that_one)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr == that_one)
	{
		ft_remove_var(prev, ptr);
	}
	return (*lst);
}

static int	delete_from_env(t_data *data, char *var)
{
	t_env_export	*temp;

	temp = data->env;
	while (temp)
	{
		if (ft_strcmp(temp->key, var) == 0)
		{
			data->env = ft_lst_delvar(&data->env, temp);
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

static int	delete_from_export(t_data *data, char *var)
{
	t_env_export	*temp;

	temp = data->export;
	while (temp)
	{
		if (ft_strcmp(temp->key, var) == 0)
		{
			data->export = ft_lst_delvar(&data->export, temp);
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

// static int delete_from_env(t_data *data, char *var)
// {
//     t_env_export *temp;
//     t_env_export *temp1;

//     temp = data->env;
//     while (temp->next)
//     {
//         if(ft_strcmp(temp->next->key, var) == 0)
//         {
//             temp1 = temp->next->next;
//             free_env_node(temp->next);
//             temp->next = temp1;
//         }
//         temp = temp->next;
//     }
//     return (EXIT_SUCCESS);
// }

// static int delete_from_export(t_data *data, char *var)
// {
//     t_env_export *temp;
//     t_env_export *temp1;

//     temp = data->export;
//     while (temp->next)
//     {
//         if(ft_strcmp(temp->next->key, var) == 0)
//         {
//             temp1 = temp->next->next;
//             free_env_node(temp->next);
//             temp->next = temp1;
//         }
//         temp = temp->next;
//     }
//     return (EXIT_SUCCESS);
// }

static int	delete_variable(t_data *data, char *var)
{
	int	status;

	status = check_variable_name(var);
	if (status != EXIT_SUCCESS)
	{
		minishell_error("unset", var, "not a valid identifier");
		return (status);
	}
	status = delete_from_env(data, var);
	if (status != EXIT_SUCCESS)
	{
		minishell_error("unset", "NULL", "env delete error\n");
		return (status);
	}
	status = delete_from_export(data, var);
	if (status != EXIT_SUCCESS)
	{
		minishell_error("unset", "NULL", "export delete error\n");
		return (status);
	}
	return (status);
}

int	unset(t_data *data, char **args) // int unset(t_data *data)
{
	int	i;
	int	status;
	int	flag;

	flag = 0;
	status = 0;
	if (!args[1])
		return (EXIT_SUCCESS);
	i = 1;
	while (args[i])
	{
		if (check_unset_name(args[i]) == EXIT_SUCCESS)
			status = delete_variable(data, args[i]);
		else
		{
			flag = EXIT_FAILURE;
			minishell_error("unset", args[i], "not a valid identifier");
		}
		i++;
	}
	if (flag)
		return (EXIT_FAILURE);
	return (status);
}
