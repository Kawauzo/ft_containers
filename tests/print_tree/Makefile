# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfourner <lfourner@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 15:44:23 by lfourner          #+#    #+#              #
#    Updated: 2021/11/09 16:28:44 by lfourner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# General #
NAME = print_rb_tree

# Directories #
DIR_INC		= ./includes/
DIR_SRC		= ./
DIR_OBJ		= ./objs/

# Files #
SRCS	= red_black_print.cpp
		  

OBJ		= ${SRCS:.cpp=.o}
OBJS	= ${addprefix ${DIR_OBJ}, ${OBJ}}


# Compiler #
CC		= clang++
CFLAGS	= ${DEBUGFLAGS} -Wall -Wextra -Werror -std=c++98
DEBUGFLAGS = -g -fsanitize=address

# Remove #
RM = rm -f

# Rules #
${DIR_OBJ}%.o:	${DIR_SRC}%.cpp
				@mkdir -p ${DIR_OBJ}
				${CC} ${CFLAGS} -c $< -o $@

$(NAME):	${OBJS}
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

