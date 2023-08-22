NAME = cub3d

<<<<<<< HEAD
<<<<<<< HEAD
SRCS =  raycasting_mal.c make_map.c map.c normalize_map.c #parser.c gestion_textures.c 
=======
SRCS =  raycasting.c make_map.c map.c parser.c gestion_textures.c \
normalize_map.c player.c keys.c render.c cub3d.c
>>>>>>> 05cf54b375f561279f0488141c0608e41c1b78a9
=======
SRCS =  raycasting.c make_map.c map.c parser.c gestion_textures.c \
normalize_map.c player.c keys.c render.c cub3d.c
>>>>>>> 889255b8d34a9634f7269072b993843bbaa805b8
OBJS	= $(SRCS:.c=.o)

LIBFT_A = libft.a

CC		= gcc

MLX =  -framework OpenGL -framework Appkit libmlx.a

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