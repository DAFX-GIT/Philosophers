# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/05 13:39:36 by adastugu          #+#    #+#              #
#    Updated: 2026/01/09 17:42:48 by adastugu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME_BONUS = philo_bonus

RM = rm -rf

CC = cc
CFLAGS = -Wall -Wextra  -g -pthread -Werror

INC_DIR = .

MANDATORY_DIR = srcs/mandatory
COMMON_DIR = srcs/common
BONUS_DIR = srcs/bonus

MANDATORY_SRCS = main.c routine.c forks.c
COMMON_SRCS = parse.c utils.c

OBJS_DIR = objs

OBJS_MANDATORY = $(addprefix $(OBJS_DIR)/, $(MANDATORY_SRCS:.c=.o))
OBJS_COMMON = $(addprefix $(OBJS_DIR)/, $(COMMON_SRCS:.c=.o))

OBJS = $(OBJS_MANDATORY) $(OBJS_COMMON)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(INC_DIR)

$(OBJS_DIR)/%.o: $(MANDATORY_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

$(OBJS_DIR)/%.o: $(COMMON_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)


clean : 
	$(RM) $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all