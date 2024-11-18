/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:20:11 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/16 20:33:38 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_value(struct t_env_export *env, char *key)
{
    struct t_env_export *temp;

    temp = env;
    while(temp)
    {
        if(ft_strcmp(temp->key, key) == 0)
            return (temp->value);
        temp = temp -> next;
    }
    return (NULL);
}

int count_env_len(struct t_env_export *env)
{
    struct t_env_export *temp;
    int len = 0;
    
    temp = env;
    while(temp)
    {
        len++;
        temp = temp->next;
    }
    return (len);
}

char **list_to_array(struct t_env_export *env)
{
    char **matrix;
    struct t_env_export *temp;
    int i;
    int len;
    char *tmp;

    len = count_env_len(env);
    matrix = (char **)malloc(sizeof(char *) * (len + 1));
    if(!matrix)
        return (NULL);
    i = 0;
    temp = env;
    while (temp)
    {
        tmp = ft_strjoin(temp->key, "=");
        matrix[i] = ft_strjoin(tmp, temp->value);
        free(tmp);
        // printf("%s\n", matrix[i]);
        if(!matrix[i])
            return (free_array(matrix), NULL);
        i++;
        temp = temp->next;
    }
    matrix[i] = NULL;
    return (matrix);
}

int is_builtin(char *cmd)
{
    if(cmd && (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
        || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
        || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
        || ft_strcmp(cmd, "exit") == 0))
        return (1);
    return (0);
}

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

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
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
