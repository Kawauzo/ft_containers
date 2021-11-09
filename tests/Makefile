# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfourner <lfourner@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 15:44:23 by lfourner          #+#    #+#              #
#    Updated: 2021/11/09 15:00:22 by lfourner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# General #
NAME = test_all
NAMEFT = test_ft
NAMEOG = test_og

# Directories #
DIR_INC		= ./includes/
DIR_SRC		= ./
DIR_OUT		= ./output_cmp/
DIR_OBJ		= ./objs/

# Files #
SRC		= main_test.cpp map_tst.cpp vector_tst.cpp stack_tst.cpp
SRCS	= ${addprefix ${DIR_OUT}, ${SRC}}
		  

OBJ		= ${SRCS:.cpp=.o}
OBJS	= ${addprefix ${DIR_OBJ}, ${OBJ}}

OBJOG	= ${SRCS:.cpp=_og.o}
OBJOGS	= ${addprefix ${DIR_OBJ}, ${OBJOG}}


# Compiler #
CC		= clang++
CFLAGS	= ${DEBUGFLAGS} -Wall -Wextra -Werror -std=c++98
DEBUGFLAGS = -g #-fsanitize=address

# Remove #
RM = rm -f

# Rules #
${DIR_OBJ}%.o:	${DIR_SRC}%.cpp
				@mkdir -p ${DIR_OBJ}/${DIR_OUT}
				${CC} ${CFLAGS} -c -DOG $< -o ${@:.o=_og.o}  # Compile files with OG flag
				${CC} ${CFLAGS} -c $< -o $@

$(NAME):	${OBJS}
			${CC} ${CFLAGS} -DOG -o ${NAMEOG} ${OBJOGS}
			${CC} ${CFLAGS} -o ${NAMEFT} ${OBJS}


all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJB}
			${RM} -r ${DIR_OBJ}

fclean:		clean
			${RM} ${NAME}
			${RM} ${NAMEOG}

re:			fclean all

.PHONY:		all clean fclean re

