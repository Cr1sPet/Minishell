NAME		=	minishell

SRCS		=	./src/main.c\
				./src/termcap/get_cmd.c\
				./src/termcap/crs_strjoin.c\
				./src/termcap/crs_utils.c\
				

HEADER		=	./includes/

LIBFT		=	libft/libft.a

OBJ			=	$(SRCS:.c=.o)

OBJ_B		=	$(SRCS_B:.c=.o)

CC			=	gcc

RM			=	rm -rf

# FLAGS		=	-Wall -Wextra -Werror 

DEBAG		=	-g

TERM		=	-ltermcap -lncurses

.PHONY		:	all clean fclean re bonus

all			:	$(NAME)

$(NAME)		:	$(OBJ)
						$(MAKE) all -C ./libft
						$(MAKE) bonus -C ./libft
						$(CC) $(FLAGS) $(OBJ) ${LIBFT} -o $(NAME) $(TERM)

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