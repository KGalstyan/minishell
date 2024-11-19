/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:51:02 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/19 21:46:23 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# define MALLOC_ERR 1
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
void minishell_error2(char *command, char *arg, char *message);
int check_variable_name(char *name);
void parse_error(char *arg);

//---- Global exit status
void set_g_exit_status(int new_status);
int get_g_exit_status();


//---- Clean data -----
void				clean_data(t_data *data);
void				exit_shell(t_data *data, int exit_signal);
void free_env_node(struct t_env_export *node);
void				free_env_export(struct t_env_export *env_export);

// ---- signal
void init_signals(void);


#endif
