# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/05 13:39:36 by adastugu          #+#    #+#              #
#    Updated: 2026/01/21 14:21:01 by adastugu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME_BONUS = philo_bonus

RM = rm -rf

CC = cc
CFLAGS = -Wall -Wextra  -g -pthread -Werror#-O3  

INC_DIR = .

MANDATORY_DIR = srcs/mandatory
COMMON_DIR = srcs/common
BONUS_DIR = srcs/bonus

MANDATORY_SRCS = main.c routine.c forks.c ini.c monitor.c checks.c free.c utils.c
COMMON_SRCS = parse.c minilft.c ft_split.c
BONUS_SRCS = main_bonus.c routine_bonus.c monitor_bonus.c ini_bonus.c forks_bonus.c checks_bonus.c free_bonus.c utils_bonus.c

OBJS_DIR = objs
OBJS_BONUS_DIR = objs_bonus

OBJS_MANDATORY = $(addprefix $(OBJS_DIR)/, $(MANDATORY_SRCS:.c=.o))
OBJS_COMMON = $(addprefix $(OBJS_DIR)/, $(COMMON_SRCS:.c=.o))

OBJS_BONUS = $(addprefix $(OBJS_BONUS_DIR)/, $(BONUS_SRCS:.c=.o))
OBJS_COMMON_BONUS = $(addprefix $(OBJS_BONUS_DIR)/, $(COMMON_SRCS:.c=.o))

OBJS = $(OBJS_MANDATORY) $(OBJS_COMMON)
OBJS_BO = $(OBJS_BONUS) $(OBJS_COMMON_BONUS)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(INC_DIR)

$(OBJS_DIR)/%.o: $(MANDATORY_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

$(OBJS_DIR)/%.o: $(COMMON_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

$(OBJS_BONUS_DIR)/%.o: $(BONUS_DIR)/%.c | $(OBJS_BONUS_DIR)
	$(CC) $(CFLAGS) -D MODE_BONUS -c $< -o $@ -I$(INC_DIR)

$(OBJS_BONUS_DIR)/%.o: $(COMMON_DIR)/%.c | $(OBJS_BONUS_DIR)
	$(CC) $(CFLAGS) -D MODE_BONUS -c $< -o $@ -I$(INC_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_BONUS_DIR):
	@mkdir -p $(OBJS_BONUS_DIR)


clean : 
	$(RM) $(OBJS_DIR)
	$(RM) $(OBJS_BONUS_DIR)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re : fclean all

bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(OBJS_BO)
	$(CC) $(CFLAGS) $(OBJS_BO) -o $(NAME_BONUS) -I $(INC_DIR)

clean_BONUS : 
	$(RM) $(OBJS_BONUS_DIR)

bonus_fclean : clean
	$(RM) $(NAME_BONUS)

bonus_re : bonus_fclean bonus 