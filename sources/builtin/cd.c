/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:23:21 by vkostand          #+#    #+#             */
/*   Updated: 2024/10/11 16:39:01 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd ..
// cd path
int	cd_path(struct t_env_export *env, char *path)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (minishell_error("cd", "", CWD_RETRIEVING_ERROR), EXIT_FAILURE);
	if (update_env(env, "OLDPWD", cwd) != EXIT_SUCCESS)
		return (free(cwd), EXIT_FAILURE);
	if (chdir(path) != 0)
	{
		minishell_error("cd", path, "No such file or directory");
		return (free(cwd), EXIT_FAILURE);
	}
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (minishell_error("cd", "", CWD_RETRIEVING_ERROR), EXIT_FAILURE);
	if (update_env(env, "PWD", cwd) != EXIT_SUCCESS)
		return (free(cwd), EXIT_FAILURE);
	return (free(cwd), EXIT_SUCCESS);
}

// cd
int	cd_home(struct t_env_export *env)
{
	char	*cwd;
	char	*home;

	cwd = getcwd(NULL, 0);
	home = get_value_from_env(env, "HOME");
	if (!home)
	{
		minishell_error("cd", "", "HOME not set");
		return (free(cwd), EXIT_FAILURE);
	}
	if (chdir(home) != 0)
	{
		minishell_error("cd", home, "No such file or directory");
		return (free(cwd), EXIT_FAILURE);
	}
    printf("home -> %s\n", home);
    printf("cwd -> %s\n", cwd);

	if (update_env(env, "PWD", home) != EXIT_SUCCESS)
		return (free(cwd), EXIT_FAILURE);
	if (update_env(env, "OLDPWD", cwd) != EXIT_SUCCESS)
		return (free(cwd), EXIT_FAILURE);
    printf("new home -> %s\n", get_value_from_env(env, "HOME"));
    printf("new cwd -> %s\n", get_value_from_env(env, "PWD"));
    printf("stexem\n\n\n");
	return (free(cwd), EXIT_SUCCESS);
}

// cd -
int	cd_oldpwd(struct t_env_export *env)
{
	char	*pwd;
	char	*oldpwd;

	pwd = get_value_from_env(env, "PWD");
	oldpwd = get_value_from_env(env, "OLDPWD");
	if (!oldpwd)
		return (minishell_error("cd", "", "OLDPWD not set"), EXIT_FAILURE);
	if (chdir(oldpwd) != 0)
		return (minishell_error("cd", oldpwd, "No such file or directory"),
			EXIT_FAILURE);
	update_env(env, "PWD", ft_strdup(oldpwd));
	update_env(env, "OLDPWD", ft_strdup(pwd));
	ft_putendl_fd(oldpwd, 1);
    printf("\n\n\n");
	return (EXIT_SUCCESS);
}

int	cd(struct t_env_export *env, char **args)
{
	int	status;

	status = 1;
	if (!args || !env)
		return (EXIT_FAILURE);
	if (args[0] && !args[1])
		status = cd_home(env);
	else if (args[0] && args[1] && ft_strcmp(args[1], "-") == 0)
		status = cd_oldpwd(env);
	else if (args[0] && args[1])
		status = cd_path(env, args[1]);
	return (status);
}

// int cd(t_data *data, char **args) // int cd(t_data *data)
// {
//     int	status;

// 	if (!data)
// 	{
// 		minishell_error("cd", "NULL", "Data error\n");
// 		return (EXIT_FAILURE);
// 	}
//     if(args[1]) // data->commands->args[1]
//         status = change_directory(data, NULL);
//     else
//         status = change_directory(data, args[1]); //data->commands->args[1]
//     if(status != EXIT_SUCCESS)
//         return (status);
//     status = update_environement(data);
//     return (status);
// }
