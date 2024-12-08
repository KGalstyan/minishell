/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:25:29 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/07 15:57:40 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H
# include "libft.h"

typedef struct s_env_export	t_env_export;
typedef struct s_token		t_token;
typedef struct s_data		t_data;
typedef struct s_cmd		t_cmd;
typedef struct s_command	t_command;

typedef enum e_quotes		t_quotes;
typedef enum e_type			t_type;
typedef struct s_token		t_token;
typedef struct s_data		t_data;

enum						e_quotes
{
	NONE,
	SINGLE,
	DOUBLE,
};

enum						e_type
{
	PIPE,
	REDIR,
	HEREDOC,
	ENV,
	WORD,
	SPACEO,
};

struct						s_token
{
	t_token					*next;
	t_token					*prev;
	t_type					type;
	t_quotes				quotes;
	// int index;
	// char *content;
	char					*original_content;
};

typedef struct s_div
{
	int						i;
	int						quotes;
	int						start;
	int						type1;
	int						type2;
}							t_div;

typedef struct s_new_token
{
	t_token					*new;
	t_token					*ptr;
	t_token					*tmp;
	char					*new_origcont;
	char					*tmp_origcont;
	t_token					*to_free;
}							t_new_token;

typedef struct s_ptr
{
	t_token					*first;
	t_token					*last;
}							t_ptr;

int							tokenization(t_data *data);
void						free_tokens(t_data *data);
// ///////////////////////  libft functions ////////////////
// t_token	*ft_lstnew(int quotes);
// int	ft_strcmp(const char *s1, const char *s2);
// void	ft_lstadd_back(t_token **lst, t_token *new);
// char	*ft_strjoin(char *s1, char *s2);
// char *ft_strncat(const char *str, int start, int end);

t_token						*ft_lstnew(int quotes);
void						ft_lstadd_back(t_token **lst, t_token *new);
void						print_data(t_data *data);

////tokenization//////

int							fill_tokens(t_data *data, int i, int j, int quotes);
int							check_pipe_red_env(t_data *data);
int							check_quotes(t_data *data);
int							check_space(t_data *data);
void						free_data(t_data *data);
void						make_new_cont(t_data *data, t_div *div,
								char *new_cont);

int							allot_quotes_value(t_data *data);
int							tokens_insertion(t_data *data);
int							dollar_insertion(t_data *data);
int							space_insertion(t_data *data);
int							pipe_insertion(t_data *data);
int							heredoc_insertion(t_data *data);
int							single_string_insertion(t_data *data);
int							double_string_insertion(t_data *data);
void						remove_brakets(t_data *data);
void						make_new_cont(t_data *data, t_div *div,
								char *new_cont);
int							connect_tokens(t_data *data);
// void ft_lst_delone(t_token **lst, t_token *that_one);
t_token						*ft_lst_delone(t_token **lst, t_token *that_one);
t_token						*connect_lst_in_one(t_token **lst, t_token *first,
								t_token *last, int type);
t_token						*divide_lst(t_token **lst, t_token *selected,
								t_div *div);
// void connect_lst_in_one(t_token **lst, t_token *first, t_token *last);

#endif
