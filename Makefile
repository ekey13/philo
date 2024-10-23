<<<<<<< HEAD
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

=======
SRC			= init locker main monitoring more_utils parsing safe_function simulation utils write

# BSRC		= 

SRCS		= $(addsuffix .c, ${SRC})

# BSRCS		= $(addsuffix .c, ${BSRC})

OBJS		= ${SRCS:.c=.o}

# BOBJS		= ${BSRCS:.c=.o}

NAME		= philo

CC			= cc
RM			= rm -f
AR			= ar rcs
RN			= ranlib

CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME)

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${AR} ${NAME} ${OBJS}
			${RN} ${NAME}
			

clean:
			${RM} ${OBJS} ${BOBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

bonus:		${BOBJS}
			${AR} ${NAME} ${BOBJS}
			${RN} ${NAME}

.PHONY:		all bonus clean fclean re
>>>>>>> 427dfbb253e39c08f6124330c365804e82cfa5e3
