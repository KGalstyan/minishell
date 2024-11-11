/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:51:02 by vkostand          #+#    #+#             */
/*   Updated: 2024/10/11 19:37:26 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# define MALLOC_ERR 3
# define CWD_ERR 4

char				**ft_arrdup(char **env);
void				init_data(t_data *data, char **env);
int					init_export(t_data *data);
void				*free_array(char **str);
void				print_array(char **str);
int					count_array_len(char **str);
void				sort_array(char **str);
void				print_list(struct t_env_export *env);
void	minishell_error(char *cmd, char *arg, char *msg);
int check_variable_name(char *name);

//---- Clean data -----
void				clean_data(t_data *data);
void				exit_shell(t_data *data, int exit_signal);
void free_env_node(struct t_env_export *node);
void				free_env_export(struct t_env_export *env_export);


#endif