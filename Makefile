NAME		=	minishell

SRCS		=	./src/main.c ./src/parsing/parser.c ./src/parsing/dollar.c\
				./src/parsing/qoutes.c ./src/parsing/parser_utils.c\
				./src/signal/signal.c ./src/parsing/parser_pipe.c\
				./src/parsing/parser_redirect.c ./src/parsing/redirect_utils.c\
				./src/parsing/pipe_utils.c

HEADER		=	./includes/

LIBFT		=	libft/libft.a

OBJ			=	$(SRCS:.c=.o)

OBJ_B		=	$(SRCS_B:.c=.o)

CC			=	gcc

RM			=	rm -rf

FLAGS		=	-Wall -Wextra -Werror 

DEBAG		=	-g

READ		=	-lreadline

.PHONY		:	all clean fclean re bonus

all			:	$(NAME)

$(NAME)		:	$(OBJ)
						$(MAKE) all -C ./libft
						$(MAKE) bonus -C ./libft
						$(CC) $(FLAGS) $(OBJ)  ${LIBFT} -o $(NAME) $(READ) -lreadline -ltermcap -g -L/Users/$(USER)/.brew/opt/readline/lib/ -I/Users/$(USER)/.brew/opt/readline/include
%.o			:	%.c $(HEADER)
								$(CC) $(FLAGS) -I$(HEADER) $(DEBAG) -c $< -o $@

bonus		:	$(OBJ_B)
				make OBJ="$(OBJ_B)" all

clean		:
				$(MAKE) clean -C ./libft
				$(RM) $(OBJ) $(OBJ_B)

fclean		:	clean
						$(MAKE) fclean -C ./libft
						$(RM) $(NAME)

re			:	fclean $(NAME)