# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 16:20:34 by trosinsk          #+#    #+#              #
#    Updated: 2024/03/24 03:29:39 by trosinsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc -Wall -Wextra -Werror #-fsanitize=thread -g #-fsanitize=address 
RM = rm -f
SRC = main.c \
		errors_msg.c \
		philo.c \
		utils.c \
		init.c \
		big_brother.c \
		utils2.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) 
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)

re: fclean all