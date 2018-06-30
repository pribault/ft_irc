# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    client.Makefile                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pribault <pribault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/30 10:56:18 by pribault          #+#    #+#              #
#    Updated: 2018/06/30 11:33:20 by pribault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	client
CC =	clang
FLAGS =	-Wall -Wextra -Werror

DIR =		client
SRC_DIR =	src
OBJ_DIR =	.obj

SRC =	client.c		flags.c\
		client_callbacks.c\
		message_callbacks.c\
		packet.c		output.c\
		send.c			send_2.c\
		user_command.c\
		prefix.c		command.c\
		param.c			receive.c\
		receive_2.c		receive_3.c\
		receive_4.c		receive_5.c\
		receive_6.c\
		user_commands.c	user_commands_2.c
OBJ =		$(sort $(SRC:%.c=$(OBJ_DIR)/$(DIR)/%.o))
INCLUDES =	client.h rfc.h
INCLUDE =	$(INCLUDES:%.h=include/%.h)

N =			0
MAX =		$(words $(OBJ))
COMPILED =	false

LIBFT =			libft
LIBFT_INC_DIR =	$(LIBFT)/include
LIBFT_INC =		libft.h\
				ft_printf.h\
				ft_joinf.h\
				malloc.h\
				structs.h\
				prototypes.h

LIBSOCKET =			libsocket
LIBSOCKET_INC_DIR =	$(LIBSOCKET)/include
LIBSOCKET_INC =		libsocket.h\
					libsocket_defines.h\
					libsocket_enums.h\
					libsocket_structures.h

DEPENDENCIES =	$(sort .Makefiles/$(NAME).Makefile\
				$(LIBFT_INC:%.h=$(LIBFT_INC_DIR)/%.h)\
				$(LIBSOCKET_INC:%.h=$(LIBSOCKET_INC_DIR)/%.h))

.PHONY: clean fclean all re norme

all: $(NAME)
	@if [ $(COMPILED) = true ]; then echo "\033[0m\033[38;5;124m[$(DIR) ∎∎∎∎] \033[0m🐼  \033[38;5;199m$(NAME) done\033[0m"; else echo "\033[0m\033[38;5;124m[$(DIR) ∎∎∎∎] \033[0m🦋  \033[38;5;199mnothing to be done for $(NAME)\033[0m"; fi

$(OBJ_DIR):
	@mkdir $@

$(OBJ_DIR)/$(DIR): | $(OBJ_DIR)
	@mkdir $@

$(OBJ_DIR)/$(DIR)/%.o: $(SRC_DIR)/$(DIR)/%.c $(INCLUDE) $(DEPENDENCIES) | $(OBJ_DIR)/$(DIR)
	@$(CC) $(FLAGS) -fPIC -I include -I $(LIBFT_INC_DIR) -I $(LIBSOCKET_INC_DIR) -o $@ -c $<
	@$(eval N=$(shell echo $$(($(N)+1))))
	@$(eval PERCENT=$(shell echo $$((($(N)*100)/$(MAX)))))
	@printf "\033[0m\033[38;5;124m[$(DIR) \033[38;5;7m%3u%%\033[38;5;124m] \033[0m🍇  \033[38;5;207m$(@:$(OBJ_DIR)/$(DIR)/%.o=%.o) done\033[0m\n" $(PERCENT)

$(NAME): $(OBJ) $(LIBFT)/libft.a $(LIBSOCKET)/libsocket.a
	@$(CC) -o $@ $(OBJ) -L $(LIBSOCKET) -lsocket -L $(LIBFT) -lft
	$(eval COMPILED=true)

clean:
	@rm -rf $(OBJ_DIR)/$(DIR)
	@echo "\033[0m\033[38;5;124m[$(DIR) ∎∎∎∎] \033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0m\033[38;5;124m[$(DIR) ∎∎∎∎] \033[0m\033[38;5;87m$(NAME) removed\033[0m"

norme:
	@norminette $(OBJ:$(OBJ_DIR)/%.o=$(SRC_DIR)/%.c) $(INCLUDE)

re: fclean all
