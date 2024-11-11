/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:18:48 by vkostand          #+#    #+#             */
/*   Updated: 2024/10/09 21:32:55 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int update_workdirs(t_data *data, char *new_path)
// {
//     if(!data)
//     {
//         minishell_error("cd", NULL, "Data error\n");
//         return (EXIT_FAILURE);
//     }
//     free(data->old_work_dir);
//     data->old_work_dir = NULL;
//     data->old_work_dir = ft_strdup(data->work_dir);
//     free(data->work_dir);
//     data->work_dir = ft_strdup(new_path);
//     if(!data->old_work_dir || !data->work_dir)
//     {
//         minishell_error("cd", NULL, "Memory allocation error\n");
//         return (EXIT_FAILURE);
//     }
//     return (EXIT_SUCCESS);
// }
