
#Compiler and flags
CC    = cc -g
FLAGS = -Wall -Wextra -Werror

# Colours                                                                                                
BGRED   = \033[0;41m
BGREEN  = \033[0;42m
BGYELL  = \033[0;43m
BGBLUE  = \033[0;44m
BGPURP  = \033[0;45m
BGCYAN  = \033[0;46m
NC      = \033[0m

# Executable name
NAME = philo

# Project files
SOURCES = main.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
		@printf "$(BGCYAN) Gathering Philosophers... $(NC)\n"
		$(CC) $(OBJECTS) $(FLAGS) -o $(NAME)
		@printf "$(BGCYAN) Philosophers at the table!! $(NC)\n"

$(OBJECTS_DIR): sources/%.c
		@printf "$(BGBLUE) Setting the table... $(NC)\n"
		mkdir -p $(@D)
		$(CC) -I includes $(FLAGS) -c $< -o $@
		@printf "$(BGBLUE) Table set!! $(NC)\n"

clean:
        @printf "$(BGYELL) Deleting created objects... $(NC)\n"
        rm -f $(OBJECTS)

fclean: clean
        @printf "$(BGYELL) Deleting executables... $(NC)\n"
        rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
