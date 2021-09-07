# General #
NAME = test_ft
NAMEOG = test_og

# Directories #
DIR_INC		= ./includes/
DIR_SRC		= ./
DIR_OBJ		= ./objs/

# Files #
SRC		= main_test.cpp

OBJ		= ${SRC:.cpp=.o}
OBJS	= ${addprefix ${DIR_OBJ}, ${OBJ}}


# Compiler #
CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -std=c++98

# Remove #
RM = rm -f

# Rules #
${DIR_OBJ}%.o:	${DIR_SRC}%.cpp
				@mkdir -p ${DIR_OBJ}
				${CC} ${CFLAGS} -c $< -o $@

$(NAME):	${OBJS}
			${CC} ${CFLAGS} -DOG -o ${NAMEOG} ${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJB}
			${RM} -r ${DIR_OBJ}

fclean:		clean
			${RM} ${NAME}
			${RM} ${NAMEOG}

re:			fclean all

.PHONY:		all clean fclean re

