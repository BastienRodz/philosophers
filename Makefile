YELLOW			= \033[1;33m
GREEN			= \033[1;32m

SRCS			= srcs/philo.c\
					srcs/philo_utils.c

OBJS			= $(SRCS:.c=.o)

CC				= clang
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g3

NAME			= philo

INCLUDE			= -I ./includes/

all:			$(NAME)

.c.o:
				@$(CC)  $(INCLUDE) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				@echo "\n${GREEN} |   Compiling Philosophers"
				@${CC} ${CFLAGS} ${OBJS} -o ${NAME} $(INCLUDE)
				@echo "${YELLOW}          [OK]\n"

clean:
				@echo "\n${GREEN} |   Cleaning Files"
				@$(RM) $(OBJS)
				@echo "${YELLOW}          [OK]\n"

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
