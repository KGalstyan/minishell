/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:57:05 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/24 20:46:12 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_data(t_data *data, char **env)
{
    // ft_memset(data, 0, sizeof(data));
    ft_bzero(data, sizeof(data));
    data->pipe_count = 0;
    data->pipe_index = 0;
    data->env = init_env(env);
    data->export = init_env(env);
    clarify_shlvl(data->env);
    clarify_shlvl(data->export);
    data->export = add_oldpwd(data->export);
    data->env = add_oldpwd(data->env);
    data->export = merge(data->export, ft_strcmp);
    data->tokens = NULL;
    data->current = NULL;
}