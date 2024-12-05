/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:17:10 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/02 16:31:43 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

//# define PATH_MAX 1024
# define CWD_RETRIEVING_ERROR \
	"error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory"

/*
	cd functions
*/

int					cd(t_data *data, char **args);
int					update_workdirs(t_data *data, char *new_path);

/*
	echo functions
*/
int					has_option(char *str);
int					echo(char **args);

/*
	env functions
*/
struct t_env_export	*init_env(char **env);
void				clarify_shlvl(struct t_env_export *env_export);
char				*get_value_from_env(struct t_env_export *env, char *key);
int					update_env(struct t_env_export *env, char *key,
						char *value);
char				*find_key(char *key_value);
char				*find_value(char *key_value);
int					env(t_data *data);

/*
	export functions
*/
int					count_export_len(t_data *data);
char				*create_export_value(char **env, int i);
void				print_export(struct t_env_export *export);
struct t_env_export	*add_oldpwd(struct t_env_export *env);
struct t_env_export	*mid_point(struct t_env_export *head);
struct t_env_export	*merge(struct t_env_export *begin, int (*cmp)());
// int 				export(struct t_env_export *export, char **args);
// struct t_env_export	*export(struct t_env_export *export, char **args);
int					export(t_data *data, char **args);

/*
	pwd functions
*/
int					pwd(t_data *data);

/*
	unset functions
*/
int					unset(t_data *data, char **args); // int unset(t_data *data)

/*
	exit functions
*/
int					builtin_exit(t_data *data);
// void builtin_exit(t_data *data);

/*
	builtin helper functions
*/
int					check_variable_name(char *name);
char				*get_value(struct t_env_export *env, char *key);
char				**list_to_array(struct t_env_export *env);
int					is_builtin(char *cmd);
int					ft_isspace(char c);

void				set_clean_exit(t_data *data, int status);
int					check_unset_name(char *name);
void				ft_remove_var(struct t_env_export *prev,
						struct t_env_export *ptr);

#endif
