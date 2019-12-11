# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/11 11:35:35 by mnaji             #+#    #+#              #
#    Updated: 2019/12/11 16:39:03 by mnaji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef VERBOSE
.SILENT:
endif

NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

SRC_FILES = main.c parsing.c free.c split_line_cut.c
OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

all: $(OBJ) $(LIBFT) $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@gcc $(FLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@gcc $(OBJ) -L $(LIBFT_DIR) -lft -o $(NAME)
	@echo "\033[32m$(NAME) generated!\033[0m"

clean:
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re obj
