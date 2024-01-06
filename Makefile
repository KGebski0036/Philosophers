# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/06 15:31:39 by kgebski           #+#    #+#              #
#    Updated: 2023/06/07 17:47:48 by kgebski          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = philo
CFLAGS      =  -pthread -Wall -Wextra -Werror -O3 -g
HDRS_DIR    = ./inc/
SRC_DIR     = ./src

SRCS	= src/_main.c src/init.c src/symulation.c src/utils.c src/philo_action.c
HDRS	= -I$(HDRS_DIR)
OBJS	= $(SRCS:.c=.o)


all: ${NAME}

${NAME}: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o:
	gcc ${CFLAGS} -c $< -o ${<:.c=.o} -I ${HDRS_DIR}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re ${NAME}