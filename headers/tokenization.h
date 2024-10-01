/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:25:29 by vkostand          #+#    #+#             */
/*   Updated: 2024/09/26 14:38:33 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H
#include "libft.h"

typedef enum s_quotes t_quotes;
typedef enum s_type t_type;
typedef struct s_token t_token;

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

t_token	*ft_lstnew(int quotes);
int	ft_strcmp(const char *s1, const char *s2);
void	ft_lstadd_back(t_token **lst, t_token *new);
void ft_lst_delone(t_token **lst, t_token *that_one);
void connect_lst_in_one(t_token **lst, t_token *first, t_token *last);


#endif