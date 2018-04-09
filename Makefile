CLIENT = client
SERVER = server
EXTENSION = .Makefile
MAKE_DIR = .Makefiles
CLIENT_MAKEFILE = $(MAKE_DIR)/$(CLIENT)$(EXTENSION)
SERVER_MAKEFILE = $(MAKE_DIR)/$(SERVER)$(EXTENSION)
LIBFT = libft
LIBSOCKET = libsocket

.PHONY: all clean fclean re $(CLIENT) $(SERVER) $(LIBFT) $(LIBSOCKET)

all: $(CLIENT) $(SERVER)

$(LIBFT):
	@make -C $(LIBFT)

$(LIBSOCKET):
	@make -C $(LIBSOCKET)

$(CLIENT): $(LIBFT) $(LIBSOCKET)
	@make -f $(CLIENT_MAKEFILE)

$(SERVER): $(LIBFT) $(LIBSOCKET)
	@make -f $(SERVER_MAKEFILE)

clean:
	@make -C $(LIBFT) clean
	@make -C $(LIBSOCKET) clean
	@make -f $(CLIENT_MAKEFILE) clean
	@make -f $(SERVER_MAKEFILE) clean

fclean:
	@make -C $(LIBFT) fclean
	@make -C $(LIBSOCKET) fclean
	@make -f $(CLIENT_MAKEFILE) fclean
	@make -f $(SERVER_MAKEFILE) fclean

re:
	@make -C $(LIBFT) re
	@make -C $(LIBSOCKET) re
	@make -f $(CLIENT_MAKEFILE) re
	@make -f $(SERVER_MAKEFILE) re
