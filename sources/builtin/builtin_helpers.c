/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:20:11 by vkostand          #+#    #+#             */
/*   Updated: 2024/10/31 15:24:25 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_variable_name(char *name)
{
    int i;

    if(!name)
        return (EXIT_FAILURE);
    if(name[0] && !ft_isalpha(name[0]) && name[0] != '_')
        return (EXIT_FAILURE);
    i = 1;
    while(name[i] && name[i] != '=')
    {
        if(name[i] != '_' && !ft_isalnum(name[i]))
            return (EXIT_FAILURE);
        i++;
    }
    return (EXIT_SUCCESS);
}

// struct t_env_export *new_node(char *env)
// {
//     struct t_env_export *new_node;

//     new_node = (struct t_env_export *)malloc(sizeof(struct t_env_export));
//     if(!new_node)
//         return (NULL);
//     new_node->key = find_key(env);
//     new_node->value = find_value(env);
//     new_node->next = NULL;
// }
