NAME = PmergeMe
CC = c++
CFLAGS = -std=c++98 -MMD -Wall -Wextra -Werror -O3
FULL ?= 0

SRCS = main.cpp PmergeMe.cpp
OBJ_DIR = obj
OBJ = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
DEPS = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -DFULL=$(FULL) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -DFULL=$(FULL) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

full: FULL = 1
full: re

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
