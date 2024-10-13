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
