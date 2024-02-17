# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 16:20:34 by trosinsk          #+#    #+#              #
#    Updated: 2024/02/17 20:29:47 by trosinsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc -Wall -Wextra -Werror #-fsanitize=address -g
RM = rm -f
SRC = main.c \
		errors_msg.c \
		philo.c \
		utils.c \
		init.c \
		monitor.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) 
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)

re: fclean all