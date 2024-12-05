NAME = minishell

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3 #-lreadline
CC = cc 

SRCS = main.c

HEADER =  libft.h \
          helpers.h \
          builtin.h \
          minishell.h \
          tokenization.h

VALIDATION = 

HELPERS = merge.c \
           helpers.c \
           clean_data.c \
           array_utils.c \
           init_export.c \
           initialization.c 

EXECUTION = processes.c \
            lexer.c \
            commands.c \
            chisht_command.c \
            execute.c \
            signal.c \
            redirs.c \
            heredoc.c \
            redir_helper.c \
            execute_helper.c \
            execute_helper_2.c \
            pipe.c

TOKENIZATION = tokenization.c \
               tokenization_utils.c \
               tokens_quotes_type.c \
               tokens_insertion.c \
               list_functions.c \
                 brakets_insertion.c \
               tokens_insertion_2.c \
                dollar_insertion.c \
                connect_lists.c 

BUILTIN = cd.c \
         env.c \
         pwd.c \
         echo.c \
         exit.c \
         unset.c \
         export.c \
         builtin_helpers.c \
         builtin_helpers_2.c


LIBFT = ft_lstadd_back.c \
        ft_atoi.c \
        ft_itoa.c \
        ft_strchr.c \
        ft_strcmp.c \
        ft_lstnew.c \
        ft_strdup.c \
        ft_strlen.c \
        ft_strjoin.c \
        ft_strncmp.c \
        ft_isalpha.c \
        ft_isdigit.c \
        ft_isalnum.c \
        ft_putstr_fd.c \
        ft_putchar_fd.c \
        ft_putendl_fd.c \
        ft_substr.c \
        ft_memset.c \
		    ft_split.c \
		    ft_strlcpy.c \
        ft_strncat.c \
        ft_bzero.c 

OBJ_DIR = ./objects/
SRCS_DIR = ./sources/
HEADER_DIR = ./headers/
LIBFT_DIR = ./sources/libft/
BUILTIN_DIR = ./sources/builtin/
HELPERS_DIR = ./sources/helpers/
EXECUTION_DIR = ./sources/execution/
VALIDATION_DIR = ./sources/validation/
TOKENIZATION_DIR = ./sources/tokenization/

$(shell mkdir -p $(OBJ_DIR))

SRCS := $(addprefix $(SRCS_DIR), $(SRCS))
LIBFT := $(addprefix $(LIBFT_DIR), $(LIBFT))
HEADER := $(addprefix $(HEADER_DIR), $(HEADER)) 
BUILTIN := $(addprefix $(BUILTIN_DIR), $(BUILTIN))
HELPERS := $(addprefix $(HELPERS_DIR), $(HELPERS))
EXECUTION := $(addprefix $(EXECUTION_DIR), $(EXECUTION))
VALIDATION := $(addprefix $(VALIDATION_DIR), $(VALIDATION))
TOKENIZATION := $(addprefix $(TOKENIZATION_DIR), $(TOKENIZATION))

SRCS += $(LIBFT)
SRCS += $(BUILTIN)
SRCS += $(HELPERS)
SRCS += $(EXECUTION)
SRCS += $(VALIDATION)
SRCS += $(TOKENIZATION)

OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

all: config ${NAME} 

config:
	mkdir -p readline_local
	./readline_config.sh readline_local

${NAME}: ${OBJS} Makefile
	@${CC} ${CFLAGS}  -I$(HEADER_DIR) -I./readline_local/include ${OBJS} -Lreadline_local/lib -lreadline -o ${NAME}

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS)  -I$(HEADER_DIR) -I./readline_local/include -c $< -o $@

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re
