/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:25:48 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/05 19:56:46 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "readline/readline.h"
#include "readline/history.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/wait.h>

#include <termios.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define in 0
#define out 1
#define PIPE_MAX 2
#define HEREDOC_FILE ".tmp_file"

typedef struct s_env_export t_env_export;
typedef struct s_token t_token;
typedef struct s_data t_data;
typedef struct s_cmd t_cmd;
typedef struct s_command t_command;

struct s_data
{
    // Vitali
    struct  t_env_export *export;
    struct  t_env_export *env;
    int	    (*fd)[2];
    int     pipe_count;
    int     pipe_index;
    int *pid;
    int index;

    // Karen
    int i;
    int j;
    int quotes_flag;
    int type;
	char *value;
	char *new_limiter;
    t_token *tokens;
    t_token *current;
    t_command *commands;
    t_command *curr_cmd;
    char *input;
};

struct t_env_export
{
    char *key;
    char *value;
    struct t_env_export *next;
};

typedef struct 	s_heredoc
{
    char *cur;
}				t_heredoc;

#include "libft.h"
#include "helpers.h"
#include "builtin.h"
#include "execution.h"
#include "tokenization.h"

#endif
