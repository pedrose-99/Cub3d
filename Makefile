NAME = cub3d

SRCS =  parser.c gestion_textures.c make_map.c normalize_map.c
OBJS	= $(SRCS:.c=.o)

LIBFT_A = libft.a

CC		= gcc

MLX =  -L. -lmlx -framework OpenGL -framework Appkit

CCFLAGS	= -Wall -Werror -Wextra -Ilibft 

.c.o:
	${CC} ${CCFLAGS} -c $< -o ${<:.c=.o} -I.

$(NAME): $(OBJS) $(LIBFT_A)
			$(CC) $(CCFLAGS) $(MLX) $(OBJS) $(LIBFT_A) -o $(NAME)
			
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