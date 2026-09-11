NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC =	forking.c \
		utils1.c \
		utils2.c

SRC_BONUS = bonus/forking_bonus.c \
			bonus/here_doc.c \
			bonus/utils_bonus.c

SRC_ALL = $(SRC) $(SRC_BONUS)

HDRS = pipex.h

HDRS_BONUS = $(HDRS) bonus/pipex_bonus.h

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a
INCLUDES = -I$(CURDIR) -I$(LIBFT_DIR)/include

all: $(NAME)

bonus: $(NAME_BONUS)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(NAME): $(LIBFT) $(SRC) $(HDRS) pipex.c
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(SRC) pipex.c $(LIBFT) $(INCLUDES) -o $(NAME)

$(NAME_BONUS): $(LIBFT) $(SRC_ALL) $(HDRS_BONUS) ./bonus/pipex_bonus.c
	@echo "Compiling $(NAME_BONUS)..."
	@$(CC) $(CFLAGS) $(SRC_ALL) ./bonus/pipex_bonus.c $(LIBFT) $(INCLUDES) \
		-o $(NAME_BONUS)

debug: fclean
	@$(MAKE) -C $(LIBFT_DIR) --quiet
	@$(CC) $(CFLAGS) -g $(SRC) pipex.c $(LIBFT) $(INCLUDES) -o $(NAME)

clean:
	@echo "Removing object files..."
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet

fclean: clean
	@echo "Removing build output..."
	@rm -rf $(NAME) $(NAME).dSYM $(NAME_BONUS) $(NAME_BONUS).dSYM
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet

re: fclean all

.PHONY: all bonus clean fclean re debug
.SILENT:
