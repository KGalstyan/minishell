/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:53:19 by vkostand          #+#    #+#             */
/*   Updated: 2024/09/23 14:32:18 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *create_export_content(char **env, int i)
// {
//     char *content;

//     content
// }

// char	*create_export_value(char **env, int i)
// {
// 	char	*res;
// 	int		j;

//     // printf("env -> %s\n", env[i]);
// 	res = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 3));
// 	if (!res)
// 		return (NULL);
// 	j = 0;
// 	while (env[i][j])
// 	{
// 		res[j] = env[i][j];
// 		if (res[j] == '=')
// 			break ;
// 		j++;
// 	}
// 	res[++j] = '"';
// 	while (env[i][j])
// 	{
// 		res[j + 1] = env[i][j];
// 		j++;
// 	}
// 	res[++j] = '"';
// 	res[++j] = '\0';
//     // printf("export -> %s\n", res);
// 	return (res);
// }

// int count_export_len(t_data *data)
// {
//     int i;

//     i = 0;
//     while (data->env[i] && ft_strncmp(data->env[i], "OLDPWD", 6) != 0)
//         i++;
//     if(data->env[i])
//         return (count_array_len(data->env));
//     return (count_array_len(data->env) + 1);
// }


// int init_export(t_data *data)
// {
//     int i;
//     char *str;

//     // printf("export len -> %d\n", count_export_len(data));
//     data->export = (char **)malloc(sizeof(char *) * count_export_len(data));
//     if(!data->export)
//         return (0);
//     i = 0;
//     while (data->env[i])
//     {
//         str = create_export_value(data->env, i);
//         printf("ardyunqum -> %s\n",  create_export_value(data->env, i));
//         data->export[i] = ft_strjoin("declare -x ", str);
//         if(!data->export[i])
//             return (0);
//         // free(str);
//         // printf("join yrac -> %s\n", data->export[i]);
//         i++;
//     }
//     data->export[i] = NULL;
//     sort_array(data->export);
//     // print_array(data->export);
//     // int i = 0;
//     // while (data->export[i])
//     // {
//     //     ft_strjoin("declare -x ", data->export[i]);
//     //     i++;
//     // }
//     // print_array(data->export);
//     return (1);
// }
