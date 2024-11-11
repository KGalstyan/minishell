/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:32:52 by vkostand          #+#    #+#             */
/*   Updated: 2024/10/07 18:42:56 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd(t_data *data)
{
    char pwd[PATH_MAX];

    if (!data)
	{
		minishell_error("pwd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (!getcwd(pwd, PATH_MAX))
	{
		minishell_error("pwd", "NULL", "Directory error\n");
		return (EXIT_FAILURE);
	}
    write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
    return (EXIT_SUCCESS);
}
