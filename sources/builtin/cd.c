/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:23:21 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/24 21:03:27 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd ..
// cd path
int	cd_path(t_data *data, char *path)
{
	char	*cwd;

	(void)path;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (minishell_error2("cd", "", CWD_RETRIEVING_ERROR), EXIT_FAILURE);
	if (update_env(data->env, "OLDPWD", cwd) != EXIT_SUCCESS)
		return (free(cwd), EXIT_FAILURE);
	if (update_env(data->export, "OLDPWD", cwd) != EXIT_SUCCESS)
		return (free(cwd), EXIT_FAILURE);
	if (chdir(path) != 0)
	{
		minishell_error2("cd", path, "No such file or directory");
		return (free(cwd), EXIT_FAILURE);
	}
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (minishell_error2("cd", "", CWD_RETRIEVING_ERROR), EXIT_FAILURE);
	if (update_env(data->env, "PWD", cwd) != EXIT_SUCCESS)
		return (free(cwd), EXIT_FAILURE);
	if (update_env(data->export, "PWD", cwd) != EXIT_SUCCESS)
		return (free(cwd), EXIT_FAILURE);
	return (free(cwd), EXIT_SUCCESS);
}

// cd
int	cd_home(t_data *data)
{
	char	*cwd;
	char	*home;

	cwd = getcwd(NULL, 0);
	home = get_value_from_env(data->env, "HOME");
	if (!home)
	{
		minishell_error2("cd", "", "HOME not set");
		return (free(cwd), EXIT_FAILURE);
	}
	if (chdir(home) != 0)
	{
		minishell_error2("cd", home, "No such file or directory");
		return (free(cwd), EXIT_FAILURE);
	}
	if (update_env(data->env, "PWD", home) != EXIT_SUCCESS)
		return (free(cwd), EXIT_FAILURE);
	if (update_env(data->env, "OLDPWD", cwd) != EXIT_SUCCESS)
		return (free(cwd), EXIT_FAILURE);
	if (update_env(data->export, "PWD", home) != EXIT_SUCCESS)
		return (free(cwd), EXIT_FAILURE);
	if (update_env(data->export, "OLDPWD", cwd) != EXIT_SUCCESS)
		return (free(cwd), EXIT_FAILURE);
	return (free(cwd), EXIT_SUCCESS);
}

// cd -
int	cd_oldpwd(t_data *data)
{
	char	*pwd;
	char	*oldpwd;

	pwd = get_value_from_env(data->env, "PWD");
	oldpwd = get_value_from_env(data->env, "OLDPWD");
	if (!oldpwd)
		return (minishell_error2("cd", "", "OLDPWD not set"), EXIT_FAILURE);
	if (chdir(oldpwd) != 0)
		return (minishell_error2("cd", oldpwd, "No such file or directory"),
			EXIT_FAILURE);
	if (update_env(data->env, "PWD", oldpwd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (update_env(data->env, "OLDPWD", pwd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (update_env(data->export, "PWD", oldpwd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (update_env(data->export, "OLDPWD", pwd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	ft_putendl_fd(oldpwd, 1);
	return (EXIT_SUCCESS);
}

int	cd(t_data *data, char **args)
{
	int	status;

	status = 1;
	if (!args || !data->env || !data->export)
		return (EXIT_FAILURE);
	if (args[0] && !args[1])
		status = cd_home(data);
	else if (args[0] && args[1] && ft_strcmp(args[1], "-") == 0)
		status = cd_oldpwd(data);
	else if (args[0] && args[1])
		status = cd_path(data, args[1]);
	return (status);
}
