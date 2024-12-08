/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:35:42 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/07 15:59:23 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_env_export	t_env_export;
typedef struct s_token		t_token;
typedef struct s_data		t_data;
typedef struct s_cmd		t_cmd;
typedef struct s_command	t_command;

int							ft_isalpha(int i);
int							ft_isdigit(int i);
int							ft_isalnum(int i);
int							ft_isascii(int i);
int							ft_isprint(int i);
size_t						ft_strlen(const char *s);
void						*ft_memset(void *str, int c, size_t n);
void						ft_bzero(void *str, size_t n);
void						*ft_memcpy(void *dst, const void *src, size_t n);
int							ft_tolower(int i);
int							ft_toupper(int i);
void						*ft_memmove(void *dst, const void *src, size_t len);
int							ft_strcmp(char *s1, char *s2);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
char						*ft_strchr(const char *s, int c);
int							ft_atoi(const char *str);
char						*ft_strrchr(const char *s, int c);
void						*ft_memchr(const void *s, int c, size_t n);
int							ft_memcmp(const void *s1, const void *s2, size_t n);
char						*ft_strnstr(const char *haystack,
								const char *needle, size_t len);
void						*ft_memmove(void *dst, const void *src, size_t len);
size_t						ft_strlcpy(char *dst, const char *src,
								size_t dstsize);
size_t						ft_strlcat(char *dst, const char *src,
								size_t dstsize);
void						*ft_calloc(size_t count, size_t size);
char						*ft_strdup(char *s1);

char						*ft_strndup(const char *s1, int n, int m);

char						*ft_substr(char const *s, unsigned int start,
								size_t len);
// char				*ft_strjoin(char const *s1, char const *s2);
char						*ft_strjoin(char *s1, char *s2);
char						*ft_strtrim(char const *s1, char const *set);
char						**ft_split(char const *s, char c);
void						ft_striteri(char *s, void (*f)(unsigned int,
									char *));
char						*ft_itoa(int n);
void						ft_putchar_fd(char c, int fd);
void						ft_putstr_fd(char *s, int fd);
void						ft_putendl_fd(char *s, int fd);
void						ft_putnbr_fd(int n, int fd);
char						*ft_strmapi(char const *s, char (*f)(unsigned int,
									char));
char						*ft_strncat(const char *str, int start, int end);

typedef struct s_list
{
	void					*content;
	struct s_list			*next;
}							t_list;

// t_list				*ft_lstnew(void *content);
void						ft_lstadd_front(t_list **lst, t_list *new);
int							ft_lstsize(t_list *lst);
t_list						*ft_lstlast(t_list *lst);
// void				ft_lstadd_back(t_list **lst, t_list *new);
// t_token	*ft_lstnew(int quotes);
// void		ft_lstadd_back(t_token **lst, t_token *new);

void						ft_lstdelone(t_list *lst, void (*del)(void *));
void						ft_lstclear(t_list **lst, void (*del)(void *));
void						ft_lstiter(t_list *lst, void (*f)(void *));
t_list						*ft_lstmap(t_list *lst, void *(*f)(void *),
								void (*del)(void *));

#endif
