NAME = philo

SRC = main.c utils.c threads.c actions.c

SRC_DIR = ./Src/

OBJ_DIR = ./Src/.obj/

SRCP = $(addprefix $(SRC_DIR),$(SRC))

OBJP = $(addprefix $(OBJ_DIR),$(notdir $(SRCP:.c=.o)))

CFLAGS = -Wall -Wextra -Werror -fPIE -g -pthread

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJP)
	@echo "\033[32mCompiling $(NAME) 🚀"
	@gcc $(CFLAGS) $(OBJP) -o $(NAME)
	@echo "Compiled ✅\033[0;37m"

clean:
	@echo "\033[0;31mCleaning objects 🧹"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "\033[0;31mRemoving $(NAME) 🗑\033[0;37m"
	@rm -rf $(NAME)

re: fclean all

.SILENT: $(OBJ)

.PHONY: all clean fclean re
