.PHONY: all clean bonus fclean re

NAME = cub3D

LIBFT_DIR = ./libs/libft

LIBFT = $(LIBFT_DIR)libft.a

LIBMLX_DIR = ./libs/mlx

LIBMLX = $(LIBMLX_DIR)libmlx.dylib

MAKE = make

CLEAN = clean

FCLEAN = fclean

SRC = main.c\
 	code/error.c\
 	code/map_check.c\
	code/ft_get_something.c\
	code/ft_color_pixels_and_stuff.c\
	code/ft_sprite.c\
	code/ft_key_functions.c\
	code/ft_sprite_one.c\
	code/get_info.c\
	code/get_info_one.c\
	code/get_text_info.c\
	code/ft_ini_something.c\
	code/ft_hook_functions.c\
	
OBJ = $(SRC:.c=.o)

CC = gcc

FLAG = -Wall -Werror -Wextra -g -O0

FLAGMLX = -framework OpenGL -framework AppKit

OPTION = -c -D GL_SILENCE_DEPRECATION

OPTIONOBJ = -o

DEL = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	@cd $(LIBFT_DIR) && mv ./libft.a ../../
	@cd $(LIBMLX_DIR) && mv ./libmlx.dylib ../../
	@$(CC) $(FLAG) $(OBJ) -L. -lmlx -lft $(FLAGSMLX) $(OPTIONOBJ) $(NAME)

$(LIBFT):
	@cd $(LIBFT_DIR) && $(MAKE)

$(LIBMLX):
	@cd $(LIBMLX_DIR) && $(MAKE)

%.o: %.c
	@$(CC) $(FLAG) $(OPTION) $< $(OPTIONOBJ) $@

clean:
	@$(DEL) $(OBJ)
	@cd $(LIBFT_DIR) && $(MAKE) $(CLEAN)
	@cd $(LIBMLX_DIR) && $(MAKE) $(CLEAN)
	
fclean: clean
	@$(DEL) $(NAME) ./libft.a ./libmlx.dylib
	@$(DEL) $(OBJ)
	@cd $(LIBFT_DIR) && $(MAKE) $(FCLEAN)
	
re: fclean all
