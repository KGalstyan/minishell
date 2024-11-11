/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:25:29 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/10 16:52:11 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H
#include "libft.h"

typedef enum s_quotes t_quotes;
typedef enum s_type t_type;
typedef struct s_token t_token;
typedef struct s_data t_data;


enum s_quotes
{
    NONE,
    SINGLE,
    DOUBLE,
};

enum s_type
{
    PIPE,
    REDIR,
    HEREDOC,
    ENV,
    WORD,
    SPACE,
};

struct s_token
{
    t_token *next;
    t_token *prev;
    t_type type;
    t_quotes quotes;
    //int index;
    char *content;
    char *original_content;
};

typedef struct s_div
{
    int i;
    int quotes;
    int start;
    int type1;
    int type2;

}          t_div;


void tokenization(t_data *data);
void free_tokens(t_data *data);
// ///////////////////////  libft functions ////////////////
// t_token	*ft_lstnew(int quotes);
// int	ft_strcmp(const char *s1, const char *s2);
// void	ft_lstadd_back(t_token **lst, t_token *new);
// char	*ft_strjoin(char *s1, char *s2);
// char *ft_strncat(const char *str, int start, int end);

t_token	*ft_lstnew(int quotes);
void		ft_lstadd_back(t_token **lst, t_token *new);
void print_data(t_data *data);

////tokenization//////

int fill_tokens(t_data *data, int i, int j, int quotes);
int check_pipe_red_env(t_data *data);
int check_quotes(t_data *data);
int check_space(t_data *data);
void free_data(t_data *data);

void allot_quotes_value(t_data *data);
void tokens_insertion(t_data *data);


// void ft_lst_delone(t_token **lst, t_token *that_one);
t_token *ft_lst_delone(t_token **lst, t_token *that_one);
t_token *connect_lst_in_one(t_token **lst, t_token *first, t_token *last, int type);
t_token *divide_lst(t_token **lst, t_token *selected, t_div *div);
// void connect_lst_in_one(t_token **lst, t_token *first, t_token *last);
void error_exit(t_data *data);


#endif
