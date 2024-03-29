CC = gcc
FLAGS =  -L./ -lmlx -framework OpenGL -framework Appkit -lz
CFLAGS = -Wall -Wextra -Werror
LIBFTFLAG	= -Llibft -lft
SRC_NAME =  main draw hooks init move rotate util map get_next_line \
			mouse_hook wft_substr_strdup wft_split calculate texture\
			draw_util map_util malloc_util map_util2 map_util3
RMF = rm -f

MAN_DIR = ./man_src/
MAN_SRC = $(addprefix $(MAN_DIR), $(addsuffix .c, $(SRC_NAME)))
MAN_OBJ = $(addprefix $(MAN_DIR), $(addsuffix .o, $(SRC_NAME)))
NAME = ./cub3D

BON_DIR = ./bon_src/
BON_SRC = $(addprefix $(BON_DIR), $(addsuffix _bonus.c, $(SRC_NAME)))
BON_OBJ = $(addprefix $(BON_DIR), $(addsuffix _bonus.o, $(SRC_NAME)))
BON_NAME = ./cub3D_bonus

all : lib $(NAME)

bonus : lib $(BON_NAME)
	@touch bonus

$(NAME) : $(MAN_OBJ)
	$(CC) $(CFLAGS) $(FLAGS) $^ -o $@ $(LIBFTFLAG)

$(BON_NAME) : $(BON_OBJ)
	$(CC) $(CFLAGS) $(FLAGS) $^ -o $@ $(LIBFTFLAG)

lib :
	@make -s -j -C ./libft

%.o : %.c
	$(CC) $(CFLAGS) -I $(dir $<)  -c $< -o $@

clean :
	@make clean -C ./libft
	$(RMF) $(MAN_OBJ) $(BON_OBJ) bonus

fclean : clean
	@make pclean -C ./libft
	$(RMF) $(NAME) $(BON_NAME) 

re: fclean
	make

.PHONY : all clean fclean re
