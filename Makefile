# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:37:37 by mle-biha          #+#    #+#              #
#    Updated: 2023/04/12 14:26:29 by mle-biha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --------------------------- Constant --------------------------- #

CC						= gcc
CFLAGS					= -Wall -Wextra -Werror -I.
NAME					= philo
INCLUDES				= -I $(INC_DIR)

# --------------------------- Sources --------------------------- #

# Directories
SRC_DIR				= srcs
OBJ_DIR				= objs
INC_DIR				= includes

# Sources and objects
SRC					= $(SRC_DIR)/main.c \
						$(SRC_DIR)/philo.c \
						$(SRC_DIR)/utils.c \
						$(SRC_DIR)/ft_atoi.c
OBJ					= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# --------------------------- Colors --------------------------- #

GREEN				= \e[1;32m
YELLOW				= \e[1;33m
BLUE				= \e[1;34m
MAGENTA				= \e[1;35m
NO_COLOR			= \e[0m

# --------------------------- Rules --------------------------- #

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(MAGENTA)Creating philo...$(NO_COLOR)"	
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)philo OK !$(NO_COLOR)\n"

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(INCLUDES) -o $@ -c $< $(CFLAGS) 

clean:
	@echo "\n$(YELLOW)Cleaning objects !$(NO_COLOR)"
	@rm -f $(OBJ)
	@echo "$(GREEN)Objects cleaned !$(NO_COLOR)\n"

fclean: clean
	@echo "$(YELLOW)Cleaning everything !$(NO_COLOR)"
	@rm -f $(NAME)
	@echo "$(GREEN)Everything cleaned !$(NO_COLOR)\n"

re: fclean all

.PHONY : clean fclean re