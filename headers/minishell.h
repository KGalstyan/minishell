/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:25:48 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/07 16:00:17 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include "readline/history.h"
# include "readline/readline.h"

# define IN 0
# define OUT 1
# define PIPE_MAX 2
# define HEREDOC_FILE ".tmp_file"

# include "builtin.h"
# include "execution.h"
# include "helpers.h"
# include "libft.h"
# include "tokenization.h"

typedef struct s_env_export	t_env_export;
typedef struct s_token		t_token;
typedef struct s_data		t_data;
typedef struct s_cmd		t_cmd;
typedef struct s_command	t_command;

struct						s_data
{
	t_env_export			*export;
	t_env_export			*env;
	int						(*fd)[2];
	int						pipe_count;
	int						pipe_index;
	int						*pid;
	int						index;
	char					*error;
	int						i;
	int						j;
	int						quotes_flag;
	int						type;
	char					*value;
	char					*new_limiter;
	t_token					*tokens;
	t_token					*current;
	t_command				*commands;
	t_command				*curr_cmd;
	char					*input;
};

struct						s_env_export
{
	char					*key;
	char					*value;
	t_env_export			*next;
};

#endif
