/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:03:31 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/07 16:03:42 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clarify_shlvl(t_env_export *env_export)
{
	int				shlvl;
	t_env_export	*temp;
	char			*str;

	temp = env_export;
	while (temp && ft_strcmp("SHLVL", temp->key) != 0)
	{
		temp = temp->next;
	}
	if (temp)
	{
		shlvl = ft_atoi(temp->value);
		shlvl++;
		free(temp->value);
		str = ft_itoa(shlvl % 1000);
		temp->value = ft_strdup(str);
		free(str);
	}
}

// int check_variable_name(char *str)
// {
//     // if (!str)
//     //     return (EXIT_FAILURE);
//     if(*str != '_' && !ft_isalpha(*str))
//         return (EXIT_FAILURE);
//     while(*str && (*str == '-' || ft_isalnum(*str)))
//         str++;
//     if(!str)
//         return (EXIT_FAILURE);
//     return (EXIT_SUCCESS);
// }

// void exit_shell(t_data *data, int exit_signal)
// {
//     clean_data(data);
//     exit(exit_signal);
// }

char	*parse_error(char *arg)
{
	char	*tmp;
	char	*result;

	tmp = NULL;
	result = NULL;
	tmp = ft_strjoin("minishell: syntax error near unexpected token `", arg);
	result = ft_strjoin(tmp, "'\n");
	free(tmp);
	tmp = NULL;
	return (result);
}

void	minishell_error(char *command, char *arg, char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (command != NULL)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg != NULL && ft_strlen(arg) > 0)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
}

void	minishell_error2(char *command, char *arg, char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (command != NULL)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg != NULL && ft_strlen(arg) > 0)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
}

// void	minishell_error(char *cmd, char *arg, char *msg)
// {
// 	if (!cmd)
// 		return ;
// 	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
// 	write(STDERR_FILENO, cmd, ft_strlen(cmd));
// 	write(STDERR_FILENO, ": ", 2);
// 	if (arg)
// 	{
// 		write(STDERR_FILENO, "`", 1);
// 		write(STDERR_FILENO, arg, ft_strlen(arg));
// 		write(STDERR_FILENO, "': ", 3);
// 	}
// 	if (msg)
// 		write(STDERR_FILENO, msg, ft_strlen(msg));
// 	else
// 		perror("");
// }
