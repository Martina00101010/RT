# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pberge <pberge@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/09 13:59:01 by jwisozk           #+#    #+#              #
#    Updated: 2020/03/03 02:55:40 by pberge           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
CC = gcc -g
#CFLAGS = -Wall -Wextra -Werror
SRCS_DIR = srcs
OBJS_DIR = objs
INCLUDES_DIR = includes
HEADERS = $(SRCS_DIR)/rt.h
LIBFT = $(INCLUDES_DIR)/libft/libft.a
MAKE_LIBFT = make -C $(INCLUDES_DIR)/libft
SDL2 = -F $(INCLUDES_DIR)/SDL2 -framework SDL2
#SDL2_HEADERS = -I $(INCLUDES_DIR)/SDL2/SDL2.framework/Headers/
#SDL2_IMAGE = -F SDL2 -framework SDL2_image
SRCS =	$(addprefix $(SRCS_DIR)/, \
		main.c \
        1_init.c \
        1_operations_create.c \
        1_operations_d.c \
        1_operations_v.c \
        1_rgb.c \
		1_refract.c \
        1_transform.c \
        2_camera_create.c \
        2_etc_1.c \
        2_light_create.c \
        2_obj_create.c \
        2_scene_extra.c \
        2_scene_get.c \
        2_valid.c \
        3_camera_look_at.c \
        3_camera_ray.c \
        3_lighting.c \
        3_obj_intersect.c \
        3_pixel_fill.c \
        3_pixels_get.c \
		3_transparent_colour.c \
        3_traverse_tree.c \
		3_refl_colour.c \
        3_antialiasing.c \
        3_cartoon.c \
        3_slice.c \
		4_sdl2_key_quit.c  \
        4_sdl2_main.c \
		)
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(SDL2) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)

$(LIBFT):
	@$(MAKE_LIBFT)

clean:
	@rm -Rf $(OBJS_DIR)
	@$(MAKE_LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all

.PHONY: all fclean re clean
