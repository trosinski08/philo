# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/17 21:13:33 by trosinsk          #+#    #+#              #
#    Updated: 2024/03/18 14:08:59 by trosinsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = cc -Wall -Wextra -Werror -fsanitize=thread -g #-fsanitize=address 
RM = rm -f
SRC = main_bonus.c \
		init_bonus.c \
		errors_msg_bonus.c \
		utils_bonus.c \
		sem_init_bonus.c \
		big_brother_bonus.c \
		utils2_bonus.c \
		routine_bonus.c \
		# //philo.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) 
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)

re: fclean all