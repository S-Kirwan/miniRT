NAME    = miniRT

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g3 -O0 -Iinc

SRC_DIR     = src/
OBJ_DIR     = obj/
INC_DIR     = inc/
LIB_DIR     = lib/
LIBFT_DIR   = $(LIB_DIR)/libft

LIBFT_A     = $(LIBFT_DIR)/libft.a
LIBFT_LIB   = -L$(LIBFT_DIR) -lft

SRC    = main.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJS    = $(SRC:.c=.o)
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJS))

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	$(MAKE) -sC $(LIBFT_DIR)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -I$(INC_DIR) $(LIBFT_LIB) -lm -o $(NAME)

clean:
	rm -f $(OBJECTS)
	$(MAKE) -sC $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -sC $(LIBFT_DIR) fclean

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run
