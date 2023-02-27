NAME	=	cub3D

SRCS_DIR_M	=	src/
SRCS_BASE_M	=	main.c etc.c map.c put_img.c \
				command1.c command2.c \
				get_init.c get_init2.c \
				check_map_surrounded_wall.c deque_utils1.c deque_utils2.c \
				paint_half.c \
				calculate_save_map1.c calculate_save_map2.c minimap.c
OBJS_M		=	$(SRCS_M:%.c=%.o)
SRCS_M		=	$(addprefix $(SRCS_DIR_M), $(SRCS_BASE_M))

SRCS_DIR_B 	=	src_bonus/
SRCS_BASE_B	=	main_bonus.c command_bonus.c etc_bonus.c \
					get_init_bonus.c map_bonus.c put_img_bonus.c
OBJS_B		=	$(SRCS_B:%.c=%.o)
SRCS_B		=	$(addprefix $(SRCS_DIR_B), $(SRCS_BASE_B))

INC_M	=	include
INC_B	=	include_bonus

ifdef WITH_BONUS
	OBJS	= $(OBJS_B)
	INC		= $(INC_M)
else
	OBJS = $(OBJS_M)
	INC		= $(INC_B)
endif

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
CLIB	=	-Llibft -l_seunghso -L. -lmlx -framework OpenGL -framework Appkit
LIBFT	=	libft
MLX		=	mlx

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	make -C $(LIBFT)
	make -C $(MLX)
	@$(CC) $(CFLAGS) $(CLIB) -I $(INC) $(OBJS) -o $(NAME)

%.o	:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus :
	make WITH_BONUS=1

clean	:
	rm -rf $(OBJS_M)
	rm -rf $(OBJS_B)
	make -C $(LIBFT) clean
	make -C $(MLX) clean

fclean	: clean
	rm -rf	$(NAME)
	make -C $(LIBFT) fclean

re		: fclean all

.PHONY: all bonus clean fclean re
