/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:27:50 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/07 22:04:03 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define FORK_ERR "fork: Resource temporarily unavailable"

typedef struct s_env_export	t_env_export;
typedef struct s_token		t_token;
typedef struct s_data		t_data;
typedef struct s_cmd		t_cmd;
typedef struct s_command	t_command;

int							start_shell(t_data *data);
int							lexer(t_data *data);
int							execute(t_data *data);
int							create_commands(t_data *data);
void						print_a(t_data *data);
void						free_commands(t_data *data);
void						free_one_command(t_data *data);

struct						s_command
{
	char					*name;
	char					**args;
	char					*error;
	int						stdout;
	int						stdin;
	t_command				*next;
};

t_command					*ft_lstnew_cmd(void);
void						ft_lstadd_back_cmd(t_command **lst, t_command *new);

int							create_pipes(t_data *data);
void						close_pipes(t_data *data);

void						run_builtin(t_data *data, char **args);
char						*get_command_path(char **path_args, char *cmd);
void						handle_error(t_data *data);

// --- redirs
int							handle_redir(t_data *data);
void						redir_dups(t_data *data);
// int				open_heredoc(char *limiter);
int							open_heredoc(t_data *data, char *limiter,
								int lim_status);
void						remove_heredoc_file(void);
int							open_infile(char *name);
int							open_outfile(char *name, int append);
int							have_dollar(char *str);

//--execute
void						wait_and_status(pid_t pid, int *_status);
void						get_path_and_execute(t_data *data);
void						dups(t_data *data);
void						clean_exit(t_data *data, int status);
bool						is_directory(const char *path);
int							is_absolute_path(t_data *data);

#endif
