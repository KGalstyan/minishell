/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:36:18 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/16 20:17:30 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_number(char *str)
{
	int i;

	i = 0;
	if(!str)
		return(0);
	if(str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while(str[i])
	{
		if(str[i] < '0' || str[i] > '9')
			return (0);
		++i;
	}
	return (1);
}

static unsigned long long ft_atol(char *str)
{
	unsigned long long number;
	int is_negative;
	int i;

	i = 0;
	number = 0;
	is_negative = 0;
	while(str[i] && ft_isspace(str[i]))
		++i;
	if(str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if(str[i] == '-')
			is_negative = 1;
		i++;
	}
	while(str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		number = number * 10 + (str[i] -'0');
		if(number > LLONG_MAX)
		{
			minishell_error2("exit", str, "numeric argument required");
			set_g_exit_status(255);
			exit(get_g_exit_status());
		}
		++i;
	}
	if(is_negative)
		return (-number);
	return (number);
}

void builtin_exit(t_data *data)
{
	int flag;

	flag = 0;
    write(STDOUT_FILENO, "exit\n", 5);
	if(data->commands->args && data->commands->args[1])
	{
		if(data->commands->args[2])
		{
			minishell_error2("exit", "", "too many arguments");
			set_g_exit_status(EXIT_FAILURE);
			flag = 1;
		}
		else if(is_number(data->commands->args[1]))
			set_g_exit_status(ft_atol(data->commands->args[1]) % 256);
		else
		{
			minishell_error2("exit", data->commands->args[1], "numeric argument required");
			set_g_exit_status(255);
		}
	}
	if(get_g_exit_status() < 0)
		set_g_exit_status(get_g_exit_status() + 256);
	if(!flag)
		exit (get_g_exit_status());
}