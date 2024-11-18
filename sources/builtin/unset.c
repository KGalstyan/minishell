/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:33:28 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/10 16:06:25 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int delete_from_env(t_data *data, char *var)
{
    struct t_env_export *temp;
    struct t_env_export *temp1;

    temp = data->env;
    while (temp->next)
    {
        if(ft_strcmp(temp->next->key, var) == 0)
        {
            temp1 = temp->next->next;
            free_env_node(temp->next);
            temp->next = temp1;
        }
        temp = temp->next;
    }
    return (EXIT_SUCCESS);
}

static int delete_from_export(t_data *data, char *var)
{
    struct t_env_export *temp;
    struct t_env_export *temp1;

    temp = data->export;
    while (temp->next)
    {
        if(ft_strcmp(temp->next->key, var) == 0)
        {
            temp1 = temp->next->next;
            free_env_node(temp->next);
            temp->next = temp1;
        }
        temp = temp->next;
    }
    return (EXIT_SUCCESS);
}

static int delete_variable(t_data *data, char *var)
{
    int	status;

    // printf("%s\n\n\n", var);
    status = check_variable_name(var);
    if(status != EXIT_SUCCESS)
    {
        minishell_error("unset", var, "not a valid identifier");
        return(status);
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

int unset(t_data *data, char **args) //int unset(t_data *data)
{
    int i;
    int status;
    
    status = 0;
    if(!data)
    {
        minishell_error("unset", NULL, "Data error\n");
        return (EXIT_FAILURE);
    }
    if(!args[1]) // data->commands->args
        return (EXIT_SUCCESS);
    i = 1;
    while(args[i]) // data->commands->args[i]
    {
        status = delete_variable(data, args[i]);
        i++;
    }
    return (status);
}
