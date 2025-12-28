NAME    = miniRT

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g3 -O3 -Iinc

SRC_DIR     = src/
OBJ_DIR     = obj/
INC_DIR     = inc/
LIB_DIR     = lib/
LIBFT_DIR   = $(LIB_DIR)/libft

LIBFT_A     = $(LIBFT_DIR)/libft.a
LIBFT_LIB   = -L$(LIBFT_DIR) -lft

SRC    = main.c \
		 parsing/validate_file.c \
		 parsing/receive_scene.c \
		 parsing/read_ambience.c \
		 parsing/read_colours.c \
		 parsing/read_coordinates.c \
		 parsing/parsing_utils.c \
		 parsing/read_camera.c \
		 parsing/read_ratio.c \
		 parsing/read_vectors.c \
		 parsing/read_light.c \
		 initialisation/initialise_data.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(dir $*)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	$(MAKE) -sC $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) $(LIBFT_LIB) -lm -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -sC $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
