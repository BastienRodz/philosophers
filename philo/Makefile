# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 15:58:49 by barodrig          #+#    #+#              #
#    Updated: 2022/05/06 13:12:24 by barodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ELLOW			= \033[1;33m
GREEN			= \033[1;32m

SRCS			= srcs/philo.c \
					srcs/print.c \
					srcs/init_data.c \
					srcs/init_philo.c \
					srcs/utils.c \
					srcs/free_all.c \
					srcs/time.c \
					srcs/routine_philo.c\
					srcs/routine_monitor.c

OBJS			= $(SRCS:.c=.o)

CC				= clang
RM				= rm -f
INCLUDE			= -I ./includes/
CFLAGS			= -Wall -Wextra -Werror -pthread -I./includes
NAME			= philo

all:			$(NAME)

.c.o:
				@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				@echo "\n${GREEN} |   Compiling Philosophers"
				@${CC} ${CFLAGS} ${INCLUDE} -o ${NAME} ${OBJS}
				@echo "${YELLOW}          [OK]\n"

clean:
				@echo "\n${GREEN} |   Cleaning Files"
				@$(RM) $(OBJS)
				@echo "${YELLOW}          [OK]\n"

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
