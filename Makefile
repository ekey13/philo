# Source files
SRC         = init locker main monitoring more_utils parsing safe_function simulation utils write

# Generated object files
OBJS        = $(addsuffix .o, $(SRC))

# Executable name
NAME        = philo

# Compiler and flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
LDFLAGS     = -lpthread  # Link with pthreads library

# Rules
all: $(NAME)

# Pattern rule for creating object files from source files
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

# Linking the object files into the final executable
$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

# Clean up object files and executable
clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

