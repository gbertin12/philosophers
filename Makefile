# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 19:32:13 by gbertin           #+#    #+#              #
#    Updated: 2022/08/12 17:23:52 by gbertin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc 
FLAGSSAN = -Wall -Wextra -Werror -fsanitize=address
FLAGS = -Wall -Wextra -Werror 
RM = rm -f
SRCS = main.c \
		src/create_list_of_philo.c \
		src/parsing.c \
		src/msg.c \
		utils/ft_atoi.c \
		utils/ft_strlen.c \
		utils/ft_memset.c 

HEAD = includes/philo.h 

OBJ=$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c $(HEAD)
		$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

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