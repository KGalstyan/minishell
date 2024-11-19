/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:33:28 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/18 17:46:33 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_remove_var(struct t_env_export *prev, struct t_env_export *ptr)
{
        if (prev)
            prev->next = ptr->next;
		free_env_node(ptr);
}

struct t_env_export *ft_lst_delvar(struct t_env_export **lst, struct t_env_export *that_one)
{
    struct t_env_export *ptr;
    struct t_env_export *prev;

    if (!lst || !*lst || !that_one)
        return NULL;
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
        // printf("1 -> %s\n", ptr->key);
        ft_remove_var(prev, ptr);
    }
    return(*lst);
}

static int delete_from_env(t_data *data, char *var)
{
    struct t_env_export *temp;
    // struct t_env_export *temp1;

    temp = data->env;
    while (temp)
    {
        if(ft_strcmp(temp->key, var) == 0)
        {
            data->env = ft_lst_delvar(&data->env, temp);
            return (EXIT_SUCCESS);
        }
        temp = temp->next;
    }
    return (EXIT_SUCCESS);
}

static int delete_from_export(t_data *data, char *var)
{
    struct t_env_export *temp;
    // struct t_env_export *temp1;

    temp = data->export;
    while (temp->next)
    {
        if(ft_strcmp(temp->key, var) == 0)
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
//     struct t_env_export *temp;
//     struct t_env_export *temp1;

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
//     struct t_env_export *temp;
//     struct t_env_export *temp1;

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

int check_unset_name(char *name)
{
    int i;

    if(!name)
        return (EXIT_FAILURE);
    if(name[0] && !ft_isalpha(name[0]) && name[0] != '_')
        return (EXIT_FAILURE);
    i = 1;
    while(name[i])
    {
        if(name[i] != '_' && !ft_isalnum(name[i]))
            return (EXIT_FAILURE);
        i++;
    }
    return (EXIT_SUCCESS);
}

int unset(t_data *data, char **args) //int unset(t_data *data)
{
    int i;
    int status;
    int flag;
    
    flag = 0;
    status = 0;
    if(!args[1]) // data->commands->args
        return (EXIT_SUCCESS);
    i = 1;
    while(args[i]) // data->commands->args[i]
    {
        if(check_unset_name(args[i]) == EXIT_SUCCESS)
            status = delete_variable(data, args[i]);
        else
        {
            flag = EXIT_FAILURE;
            minishell_error("unset", args[i], "not a valid identifier");
        }
        // printf("args -> %s\n", args[i]);
        i++;
    }
    if(flag)
        return (EXIT_FAILURE);
    return (status);
}
