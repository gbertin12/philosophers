# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 19:32:13 by gbertin           #+#    #+#              #
#    Updated: 2022/10/17 18:14:06 by gbertin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc 
FLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f
SRCS = philo.c \
		src/threads/check_death.c \
		src/threads/coroutine.c \
		src/threads/get_timestamp.c \
		src/threads/launch_coroutine.c \
		src/create_list_of_philo.c \
		src/handle_fork.c \
		src/create_threads.c \
		src/init_var.c \
		utils/check_int.c \
		utils/free_all.c \
		utils/ft_atoi.c \
		utils/ft_isdigit.c \
		utils/ft_llota.c \
		utils/ft_strlen.c \
		utils/ft_memset.c \
		utils/msg.c 

HEAD = includes/philo.h 

OBJ=$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c $(HEAD)
		$(CC) $(FLAGS)  -c $< -o ${<:.c=.o}

$(NAME):$(OBJ) $(HEAD)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)
		
clean: 
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re