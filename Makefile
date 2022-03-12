NAME		=	minishell

SRCS		=	./src/main.c\
				./src/exec/exec.c\
				./get_next_line/get_next_line.c\
				./src/exec/here_doc.c\
				./src/init.c\
				./src/lst_cmdadd_back.c\
				./src/lst_cmdlast.c\
				./src/lst_cmdnew.c\
				./src/builtins/echo.c\
				./src/builtins/pwd.c\
				./src/builtins/env.c\
				./src/builtins/unset.c\
				./src/builtins/change_dir.c\
				./src/builtins/export.c\
				# ./get_next_line/get_next_line_utils.c\
				# ./src/redir.c\
				
				

HEADER		=	./includes/

LIBFT		=	libft/libft.a

OBJ			=	$(SRCS:.c=.o)

OBJ_B		=	$(SRCS_B:.c=.o)

CC			=	gcc

RM			=	rm -rf

# FLAGS		=	-Wall -Wextra -Werror 

DEBAG		=	-g

READ		=	-lreadline

.PHONY		:	all clean fclean re bonus

all			:	$(NAME)

$(NAME)		:	$(OBJ)
						$(MAKE) all -C ./libft
						$(MAKE) bonus -C ./libft
						$(CC) $(FLAGS) $(OBJ) ${LIBFT} -o $(NAME) $(READ)

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
