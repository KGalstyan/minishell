/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:51:02 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/14 19:04:27 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# define MALLOC_ERR 3
# define CWD_ERR 4

typedef struct s_env_export	t_env_export;
typedef struct s_token		t_token;
typedef struct s_data		t_data;
typedef struct s_cmd		t_cmd;
typedef struct s_command	t_command;

char						**ft_arrdup(char **env);
void						init_data(t_data *data, char **env);
int							init_export(t_data *data);
void						*free_array(char **str);
void						print_array(char **str);
int							count_array_len(char **str);
void						sort_array(char **str);
void						print_list(t_env_export *env);
void						minishell_error(char *cmd, char *arg, char *msg);
void						minishell_error2(char *command, char *arg,
								char *message);
int							check_variable_name(char *name);
char						*parse_error(char *arg);
void						set_parse_error(t_data *data, char *arg);

//---- Global exit status
void						set_g_exit_status(int new_status);
int							get_g_exit_status(void);

//---- Clean data -----
void						clean_data(t_data *data);
void						exit_shell(t_data *data, int exit_signal);
void						free_env_node(t_env_export *node);
void						free_env_export(t_env_export *env_export);

// ---- signal
void						init_signals(int type);

#endif