NAME = minishell
CFLAGS = -Wall -Wextra -Werror -lreadline #-fsanitize=address
CC = cc 
SRCS =	main.c

HEADER =	minishell.h \
			tokenization.h \
			helpers.h \
			libft.h

VALIDATION = 

HELPERS =	ft_arrdup.c \
			free_array.c \
			initialization.c

TOKENIZATION =	tokenization.c \
				tokenization_utils.c \
				libft_functions.c\
				tokens_quotes_type.c \
				tokens_insertion.c \
				list_function.c

LIBFT = ft_lstadd_back.c \
		ft_lstnew.c \
		ft_strdup.c \
		ft_strlen.c

SRCS_DIR = ./sources/
HEADER_DIR = ./headers/
LIBFT_DIR = ./sources/libft/
VALIDATION_DIR = ./sources/validation/
TOKENIZATION_DIR = ./sources/tokenization/
HELPERS_DIR = ./sources/helpers/


SRCS := $(addprefix $(SRCS_DIR), $(SRCS))
HEADER := $(addprefix $(HEADER_DIR), $(HEADER)) 
LIBFT := $(addprefix $(LIBFT_DIR), $(LIBFT))
VALIDATION := $(addprefix $(VALIDATION_DIR), $(VALIDATION))
TOKENIZATION := $(addprefix $(TOKENIZATION_DIR), $(TOKENIZATION))
HELPERS := $(addprefix $(HELPERS_DIR), $(HELPERS))

SRCS += $(LIBFT)
SRCS += $(VALIDATION)
SRCS += $(TOKENIZATION)
SRCS += $(HELPERS)

OBJS = ${SRCS:.c=.o} #> ./sources/validation/a

all: ${NAME}

${NAME}: ${OBJS} Makefile 
	@${CC} ${CFLAGS} -I$(HEADER_DIR) ${OBJS} -o ${NAME} -lreadline

.c.o:
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $(<:.c=.o)

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re

