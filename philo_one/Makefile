NAME = philo_one
CFLAGS = -Wall -Wextra -Werror
CC = gcc
SRCS = ${addprefix srcs/,${shell ls srcs | grep '\.c'}}
OBJS = ${SRCS:.c=.o}
INC = -I./includes
RM = rm -f

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${INC} -o ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean:
	${RM} ${NAME}

re: fclean all

