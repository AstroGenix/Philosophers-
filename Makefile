#Compiler and flags
CC    = cc -g
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -pthread

# Colours
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# Background Colours                                                                                                
BGRED   = \033[0;41m
BGREEN  = \033[0;42m
BGYELLOW  = \033[0;43m
BGBLUE  = \033[0;44m
BGPURPLE  = \033[0;45m
BGCYAN  = \033[0;46m

# Reset Colour
NC      = \033[0m

# Executable name
NAME = philo

# Folders

SRC_DIR = sources/
OBJ_DIR = objects/

# Project files
SRC_FILES = end_sim init monitor routine utils main action

SOURCES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

OBJECTS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJ_FILES = .cache_exists

all: $(NAME)

$(NAME): $(OBJECTS)
		@$(CC) $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $(NAME)
		@echo "$(BGCYAN) Philosophers compiled! $(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_FILES)
		@echo "$(BLUE) Compiling: $(NC)$<"
		@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

$(OBJ_FILES):
	@mkdir -p $(OBJ_DIR)

clean:
		@echo "$(BGYELLOW) Deleting created objects... $(NC)"
		rm -f -r $(OBJ_DIR)
		rm -f $(OBJ_FILES)

fclean: clean
		@echo "$(BGYELLOW) Deleting executables... $(NC)"
		rm -f $(NAME)

re: fclean all
	@echo "$(BGYELLOWYELLOW) Cleaned and rebuilt everything! $(NC)"

.PHONY: all clean fclean re
