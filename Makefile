NAME = cub3d

SRCS =	make_map.c parser.c
OBJS	= $(SRCS:.c=.o)

LIBFT_A = libft.a

CC		= gcc

#READLINE = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

CCFLAGS	= -Wall -Werror -Wextra -Ilibft

.c.o:
	${CC} ${CCFLAGS} -c $< -o ${<:.c=.o} -I.

$(NAME): $(OBJS) $(LIBFT_A)
			$(CC) $(CCFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)
			
all: $(NAME)

$(LIBFT_A):
		make bonus -C libft
		cp libft/libft.a .
clean:
		make -C libft clean
		rm -f $(OBJS)
fclean: clean
		@make -C libft fclean
		rm -f libft.a
		rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re  