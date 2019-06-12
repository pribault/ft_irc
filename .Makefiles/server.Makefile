# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    server.Makefile                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pribault <pribault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/30 11:01:47 by pribault          #+#    #+#              #
#    Updated: 2019/06/12 11:01:27 by pribault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	serveur
CC =	clang
FLAGS =	-Wall -Wextra -Werror

DIR =		server
SRC_DIR =	src
OBJ_DIR =	.obj

SRC =	server.c	flags.c\
		client_callbacks.c\
		message_callbacks.c\
		output.c	packet.c\
		prefix.c	param.c\
		command.c	config.c\
		receive.c	receive_2.c\
		receive_3.c\
		send.c		send_2.c\
		send_3.c	send_4.c\
		send_5.c\
		verif.c		channels.c\
		channels_2.c
OBJ =		$(sort $(SRC:%.c=$(OBJ_DIR)/$(DIR)/%.o))
INCLUDES =	server.h rfc.h
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

DEPENDENCIES =	$(sort .Makefiles/server.Makefile\
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
	@$(CC) $(FLAGS) -o $@ $(OBJ) -L $(LIBSOCKET) -lsocket -L $(LIBFT) -lft
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
