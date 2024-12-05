/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:38:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/24 21:01:20 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] == '-')
			return (0);
		else if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 0;
	if (args && args[i])
		i++;
	while (args && args[i] && has_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args && args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putstr_fd(" ", 1);
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

// int echo(char **args)
// {

// }
