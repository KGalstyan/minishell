/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:25:48 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/13 19:46:27 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include "readline/readline.h"
#include "readline/history.h"

#include <termios.h>
#include <errno.h>
#include <string.h>

typedef struct s_command t_command;

typedef struct s_env_export t_env_export;

typedef struct s_token t_token;

typedef struct s_data t_data;


struct s_data
{
    // Vitali
    struct t_env_export *export;
    struct t_env_export *env;


    // Karen
    int i;
    int j;
    int quotes_flag;
    int type;
	t_command *commands;
	t_command *curr_cmd;
    t_token *tokens;
    t_token *current;
    char *input;
};

struct t_env_export
{
    char *key;
    char *value;
    struct t_env_export *next;
};

#include "libft.h"
#include "helpers.h"
#include "builtin.h"
#include "execution.h"
#include "tokenization.h"

// void rl_replace_line (const char *, int);
// extern void rl_clear_history (void);
void set_g_exit_status(int new_status);
int get_g_exit_status();

// void tokenization(t_data *data);
// void start_shell(t_data *data);
// void	ft_lstadd_back(t_token **lst, t_token *new);
// t_token	*ft_lstnew(void *content);

#endif
