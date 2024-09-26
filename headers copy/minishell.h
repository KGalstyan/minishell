/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:25:48 by vkostand          #+#    #+#             */
/*   Updated: 2024/09/26 19:56:02 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "tokenization.h"

typedef struct s_data
{
    char **env;
    int i;
    int j;
    int quotes_flag;
    t_token *tokens;
    t_token *current;
    char *input;
}               t_data;

#include "libft.h"
#include "helpers.h"


void start_shell(t_data *data);
void error_exit(t_data *data);

////tokenization//////

int fill_tokens(t_data *data, int i, int j, int quotes);
int check_pipe_red_env(t_data *data);
int check_quotes(t_data *data);
int check_space(t_data *data);
void free_data(t_data *data);

void allot_quotes_value(t_data *data);
void tokens_insertion(t_data *data);

#endif