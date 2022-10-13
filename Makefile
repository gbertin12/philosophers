# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 19:32:13 by gbertin           #+#    #+#              #
#    Updated: 2022/10/13 10:16:46 by gbertin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc 
FLAGSSAN = -Wall -Wextra -Werror  -pthread -fsanitize=address
FLAGS = -Wall -Wextra -Werror -pthread -g3
RM = rm -f
SRCS = philo.c \
		src/check_death.c \
		src/coroutine.c \
		src/create_list_of_philo.c \
		src/create_threads.c \
		src/free_all.c \
		src/get_timestamp.c \
		src/init_coroutine.c \
		src/init_var.c \
		src/msg.c \
		utils/check_int.c \
		utils/ft_atoi.c \
		utils/ft_isdigit.c \
		utils/ft_strlen.c \
		utils/ft_memset.c 

HEAD = includes/philo.h 

OBJ=$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c $(HEAD)
		$(CC) $(FLAGS)  -c $< -o ${<:.c=.o}

$(NAME):$(OBJ) $(HEAD)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

sanitize: $(OBJ) $(HEAD)
		$(CC) $(FLAGSSAN) $(OBJ) -o $(NAME)
clean: 
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re