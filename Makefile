SRC = ./*.c
NAME = cub

all : 
	gcc -Wextra -Werror -Wall -lmlx -framework OpenGL \
		-framework Appkit ./*.c -o $(NAME)
	./cub