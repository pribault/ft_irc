/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:54:30 by pribault          #+#    #+#             */
/*   Updated: 2018/06/30 12:39:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

/*
****************
**	includes  **
****************
*/

# include "libft.h"
# include "libsocket.h"
# include "rfc.h"

# include <arpa/inet.h>
# include <sys/stat.h>
# include <netdb.h>

/*
***************
**	defines  **
***************
*/

/*
**	colors
*/

# define COLOR_BOLD			"\e[1m"
# define COLOR_HALF			"\e[2m"
# define COLOR_ITALIC		"\e[3m"
# define COLOR_UNDERLINED	"\e[4m"
# define COLOR_CLEAR		"\e[0m"
# define COLOR_BK0		"\e[38;5;16m"
# define COLOR_R0		"\e[38;5;124m"
# define COLOR_G0		"\e[38;5;28m"
# define COLOR_B0		"\e[38;5;32m"
# define COLOR_Y0		"\e[38;5;214m"
# define COLOR_C0		"\e[38;5;45m"
# define COLOR_M0		"\e[38;5;133m"
# define COLOR_ERROR	COLOR_R0
# define COLOR_SYSTEM	COLOR_Y0
# define COLOR_INFO		COLOR_C0
# define COLOR_VERBOSE	COLOR_G0
# define COLOR_NAME		COLOR_B0

/*
**	options
*/

# define OPT_VERBOSE		BYTE(0)

/*
**	irc defines
*/

# define NICK_MAX_LEN		10

/*
**	config
*/

# define CONFIG_FILE		"server.cfg"
# define CONFIG_SEPARATORS	WHITESPACES

# define SERVNAME		"SERVNAME"
# define PORT			"PORT"
# define MOTD			"MOTD"

# define DEFAULT_SERVNAME	"MyIRC"
# define DEFAULT_PORT		"6667"
# define DEFAULT_MOTD		"motd.txt"

/*
*************
**	enums  **
*************
*/

typedef enum	e_server_error
{
	ERROR_SETTING_DEFAULT = ERROR_FT_MAX,
	ERROR_UNKNOWN_PROTOCOL,
	ERROR_UNKNOWN_DOMAIN,
	ERROR_PACKET_TOO_SMALL,
	ERROR_ALLOCATION_RETURN,
	ERROR_UNHANDLE_PACKET,
	ERROR_UNKNOWN_PACKET,
	ERROR_SETUP_FDS,
	ERROR_LOADING_CONFIG,
	ERROR_PORT_PARAMS,
	ERROR_SERVNAME_PARAMS,
	ERROR_MOTD_PARAMS,
	ERROR_CANNOT_START,
	ERROR_CORRUPTED_MEMORY
}				t_server_error;

/*
******************
**	structures  **
******************
*/

typedef struct	s_data
{
	void		*client;
	void		*ptr;
	uint64_t	size;
	char		nickname[NICK_MAX_LEN];
	char		*username;
	char		*hostname;
	char		*realname;
	uint8_t		permissions;
}				t_data;

typedef struct	s_channel
{
	char		*name;
	char		*topic;
	char		*perms;
	uint8_t		permissions;
	t_vector	clients;
}				t_channel;

typedef struct	s_env
{
	t_socket	*socket;
	char		*port;
	char		**motd;
	uint32_t	opt;
	t_protocol	protocol;
	t_domain	domain;
	t_vector	channels;
	t_vector	clients;
	char		*name;
}				t_env;

typedef struct	s_cmd
{
	char		*name;
	void		(*function)(t_env *, t_data *, t_message *);
}				t_cmd;

typedef struct	s_config_cb
{
	char		*name;
	char		*value;
	void		(*function)(t_env *, char **, uint32_t);
}				t_config_cb;

/*
******************
**	prototypes  **
******************
*/

/*
**	config
*/

int				load_config(t_env *env);
void			servname_callback(t_env *env, char **array, uint32_t n);
void			port_callback(t_env *env, char **array, uint32_t n);
void			motd_callback(t_env *env, char **array, uint32_t n);

/*
**	flags
*/

void			print_usage(void);
void			get_default(char *s, t_env *env);
void			get_protocol(t_env *env, char **args, int n);
void			get_domain(t_env *env, char **args, int n);
void			set_verbose(t_env *env);

/*
**	socket callbacks
*/

void			socket_excpt(t_socket *socket);

/*
**	client callbacks
*/

void			client_add(t_socket *socket, void *client);
void			client_del(t_socket *socket, void *client);
void			client_excpt(t_socket *socket, void *client);

/*
**	message callbacks
*/

void			message_received(t_socket *socket, void *client, t_msg *msg);
void			message_sended(t_socket *socket, void *client, t_msg *msg);
void			message_trashed(t_socket *socket, void *client, t_msg *msg);

/*
**	packet management
*/

void			treat_packet(t_socket *socket, void *client, void *ptr,
				size_t size);
char			*get_prefix(t_prefix *prefix, char *s);
char			*get_param(char *param, char *s);
char			*get_command(char *command, char *s);

/*
**	output
*/

void			enqueue_write(t_socket *socket, void *client, void *ptr,
				size_t size);
void			enqueue_str_by_fd(t_env *env, int fd, char *s);

/*
**	receive functions
*/

void			recv_unknown(t_env *env, t_data *data, t_message *msg);
void			recv_nick(t_env *env, t_data *data, t_message *msg);
void			recv_user(t_env *env, t_data *data, t_message *msg);
void			recv_list(t_env *env, t_data *data, t_message *msg);
void			recv_join(t_env *env, t_data *data, t_message *msg);
void			recv_quit(t_env *env, t_data *data, t_message *msg);
void			recv_who(t_env *env, t_data *data, t_message *msg);
void			recv_ping(t_env *env, t_data *data, t_message *msg);

/*
**	send functions
*/

void			send_error(t_env *env, t_data *data, char *error,
				char *comment);
void			send_first_welcome(t_env *env, t_data *data);
void			send_welcome(t_env *env, t_data *data);
void			send_nick(t_env *env, t_data *data, char *nick);
void			send_liststart(t_env *env, t_data *data);
void			send_list(t_env *env, t_data *data, t_channel *channel);
void			send_listend(t_env *env, t_data *data);
void			send_pong(t_env *env, t_data *data);
void			send_motdstart(t_env *env, t_data *data);
void			send_motd(t_env *env, t_data *data);
void			send_motdend(t_env *env, t_data *data);
void			send_quit(t_env *env, t_data *data, t_data *to, char *reason);
void			send_join(t_env *env, t_data *data, t_data *to,
				t_channel *channel);
void			send_who_reply(t_env *env, t_data *data, t_data *client,
				t_channel *channel);
void			send_err_no_such_server(t_env *env, t_data *data,
				char *servname);
void			send_end_of_who(t_env *env, t_data *data, char *name);

/*
**	verif functions
*/

t_bool			is_nickname_valid(char *nick);

/*
**	channel functions
*/

t_channel		*find_channel(t_vector *vector, char *name);
void			add_client_to_channel(t_env *env, t_channel *channel,
				t_data *data);
void			create_channel(t_env *env, t_vector *vector, char *name,
				t_data *data);
t_bool			is_client_in_channel(t_channel *channel, t_data *client);
void			remove_client_from_channel(t_channel *channel, t_data *client);

/*
**	others
*/

void			notify_disconnection(t_env *env, t_data *data, char *reason);

#endif
