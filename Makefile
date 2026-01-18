# Text styles
DEL_LINE =		\033[2K
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m

# Basic bright colors
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m

# Other colors
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

#Compiler Info
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinc -Ilibft -Iminilibx-linux -MMD -MP -g3

#Libraries
LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./lib/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

#Target names
NAME = miniRT

#Paths
OBJ_DIR = build
SRC_DIR = src
#$(SRC_DIR)/screen.c \
#Source Files
SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing/validate_file.c \
		$(SRC_DIR)/parsing/receive_scene.c \
		$(SRC_DIR)/parsing/read_ambience.c \
		$(SRC_DIR)/parsing/read_colours.c \
		$(SRC_DIR)/parsing/read_coordinates.c \
		$(SRC_DIR)/parsing/read_camera.c \
		$(SRC_DIR)/parsing/read_ratio.c \
		$(SRC_DIR)/parsing/read_vectors.c \
		$(SRC_DIR)/parsing/read_light.c \
		$(SRC_DIR)/parsing/read_sphere.c \
		$(SRC_DIR)/parsing/read_plane.c \
		$(SRC_DIR)/parsing/read_cylinder.c \
		$(SRC_DIR)/parsing/parsing_utils.c \
		$(SRC_DIR)/parsing/parsing_tests.c \
		$(SRC_DIR)/window_management/window_initialisation.c \
		$(SRC_DIR)/window_management/window_destruction.c \
		$(SRC_DIR)/window_management/image_initialisation.c \
		$(SRC_DIR)/window_management/event_hooks.c \

#Objects and Dependencies
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# DEP = $($(OBJ_DIR)/%.o=$(OBJ_DIR)/%.d)
# DEP = $(OBJ:.o=.d)

#Create Program
$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $@
	@echo "\n${GREEN} Created $(NAME) ${DEF_COLOR}\n"

#Create Libraries
$(LIBFT):
	@echo "\n${CYAN} ==libft= ${DEF_COLOR}"
	@make --no-print-directory -C $(LIBFT_DIR)

$(MLX_LIB):
	@echo "\n${CYAN} ==minilibx== ${DEF_COLOR}"
	@{ \
		 bar=""; \
		 max=50;\
		 while :; do \
		 	bar="$${bar}#"; \
		 	printf "\r${GREEN}[%-${max}s] ${DEF_COLOR}" "$$bar"; \
		 	sleep 0.08; \
		 done \
		 } & \
		 PID=$$!; \
		make --no-print-directory -C $(MLX_DIR) > /dev/null 2>&1; \
		 kill $$PID >/dev/null 2>&1 || true; \
		 printf "\n%0.s" $$(seq 1 $$max);

#Compile .c into Object Files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "\n${CYAN} ==$(NAME)== ${DEF_COLOR}"
	@echo "${MAGENTA} ~ ${BROWN} Compiling... ${MAGENTA}-> ${CYAN}$< ${DEF_COLOR}\n"
	@$(CC) $(CFLAGS) -I/usr/include -I$(MLX_DIR)mlx -c $< -o $@

#Build All
all: $(NAME)

#Remove Object files
clean:
	@rm -rf $(OBJ_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@make --no-print-directory -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "${YELLOW} Cleaned $(OBJ_DIR) miniRT ${DEF_COLOR}"

#Remove Everything
fclean: clean
	@rm -f $(NAME)
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "${YELLOW} Cleaned $(NAME) ${DEF_COLOR}"

#Rebuild Everything
re: fclean all

.PHONY: all clean fclean re
