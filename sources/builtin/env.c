/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:30:53 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/24 20:43:40 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int update_env(struct t_env_export *env, char *key, char *value)
{
    struct t_env_export *temp;

    temp = env;
    while(temp)
    {
        if(ft_strcmp(temp->key, key) == 0)
        {
            free(temp->value); // seg
            temp->value = ft_strdup(value); // leak
            if(!temp->value)
                return (EXIT_FAILURE);
            return (EXIT_SUCCESS);
        }
        temp = temp->next;
    }
    // env = add_oldpwd(data);
    // temp = env;
    // while(temp)
    // {
    //     if(ft_strcmp("OLDPWD", temp->key) == 0)
    //     {
    //         temp->value = ft_strdup(value);
    //     }
    //     temp = temp->next;
    // }
    // printf("stexem\n");
    // temp = malloc(sizeof(struct t_env_export));
    // if(!temp)
    //     return (MALLOC_ERR);
    // temp->key = key;//ft_strdup(key);
    // temp->value = value;//ft_strdup(value);
    
    // free(temp);
    return (EXIT_SUCCESS);
}

char *get_value_from_env(struct t_env_export *env, char *key)
{
    struct t_env_export *temp;

    temp = env;
    if(!ft_strcmp(key, "?"))
        return(ft_itoa(get_g_exit_status()));
    while(temp)
    {
        if(ft_strcmp(temp->key, key) == 0)
            return (temp->value);
        temp = temp->next;
    }
    return (NULL);
}

char *find_key(char *key_value)
{
    int i;
    char *key;

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

char *find_value(char *key_value)
{
    int i;
    int j;
    char *value;

    if (!key_value)
        return (NULL);
    i = ft_strlen(key_value) - 1;
    while (i >= 0 && key_value[i] != '=')
        i--;
    value = (char *)malloc(sizeof(char) * (ft_strlen(key_value) - i));
    if (!value)
        return (NULL);
    i++;
    j = 0;
    while (key_value[i])
    {
        value[j++] = key_value[i];
        i++;
    }
    value[j] = '\0';
    return (value);
}

struct t_env_export *init_env(char **env) 
{
    int i = 0;
    struct t_env_export *head = NULL;
    struct t_env_export *current = NULL;
    struct t_env_export *new_node;
    while (env[i])
    {
        new_node = malloc(sizeof(struct t_env_export));
        if (!new_node)
            return(NULL);
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
    return head;
}

// struct t_env_export *init_env(char **env)
// {
//     int i;
//     struct t_env_export *new_env;
//     struct t_env_export temp;

//     new_env = &temp;
//     i = 0;
//     while(env[i])
//     {
//         new_env->next = malloc(sizeof(struct t_env_export));
//         if(!new_env)
//             exit(MALLOC_ERR);
//         new_env->next->key = find_key(env[i]);
//         new_env->next->value = find_value(env[i]);
//         new_env->next->next = NULL;
//         new_env = new_env->next;
//         i++;
//     }
//     new_env = temp.next;
//     // printf("stexem\n");
//     return(new_env);
// }

int env(t_data *data)
{
    if (!data)
	{
		minishell_error("pwd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
    print_list(data->env);
    return(EXIT_SUCCESS);
}

