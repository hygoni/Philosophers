NAME = philo_one
CFLAGS = -Wall -Wextra -Werror -g
CC = gcc
SRCS = ${addprefix srcs/,${shell ls srcs | grep '\.c'}}
OBJS = ${SRCS:.c=.o}
INC = -I./includes
LIB = -L./ft_printf -lftprintf
RM = rm -f

%.o : %.c
	${CC} ${CFLAGS} ${INC} -c $< -o $@
all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${INC} ${LIB} -o ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

