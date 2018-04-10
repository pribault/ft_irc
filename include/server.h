/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:54:30 by pribault          #+#    #+#             */
/*   Updated: 2018/04/10 17:06:00 by pribault         ###   ########.fr       */
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
# define COLOR_BK0		COLOR(0, 0, 0)
# define COLOR_R0		COLOR(153, 0, 0)
# define COLOR_G0		COLOR(0, 102, 0)
# define COLOR_B0		COLOR(0, 102, 204)
# define COLOR_Y0		COLOR(255, 153, 0)
# define COLOR_C0		COLOR(0, 204, 255)
# define COLOR_M0		COLOR(153, 51, 153)
# define COLOR_ERROR	ft_get_term_color(COLOR_R0, COLOR_BK0, EFFECT_NOBACK)
# define COLOR_SYSTEM	ft_get_term_color(COLOR_Y0, COLOR_BK0, EFFECT_NOBACK)
# define COLOR_INFO		ft_get_term_color(COLOR_C0, COLOR_BK0, EFFECT_NOBACK)
# define COLOR_VERBOSE	ft_get_term_color(COLOR_G0, COLOR_BK0, EFFECT_NOBACK)
# define COLOR_NAME		ft_get_term_color(COLOR_B0, COLOR_BK0, EFFECT_NOBACK)

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

# define DEFAULT_SERVNAME	"Unicooooorn IRC"
# define DEFAULT_PORT		"6667"

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
	ERROR_SERVNAME_PARAMS
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
	uint8_t		permissions;
}				t_data;

typedef struct	s_channel
{
	char		*name;
	t_vector	clients;
}				t_channel;

typedef struct	s_env
{
	t_server	*server;
	char		*port;
	uint32_t	opt;
	int			in;
	int			out;
	int			err;
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

/*
**	flags
*/

void			print_usage(void);
void			get_default(char *s, t_env *env);
void			get_protocol(t_env *env, char **args, int n);
void			get_domain(t_env *env, char **args, int n);
void			set_verbose(t_env *env);

/*
**	server callbacks
*/

void			server_excpt(t_server *server);

/*
**	client callbacks
*/

void			client_add(t_server *server, void *client);
void			client_del(t_server *server, void *client);
void			client_excpt(t_server *server, void *client);

/*
**	message callbacks
*/

void			message_received(t_server *server, void *client, t_msg *msg);
void			message_sended(t_server *server, void *client, t_msg *msg);
void			message_trashed(t_server *server, void *client, t_msg *msg);

/*
**	packet management
*/

void			treat_packet(t_server *server, void *client, void *ptr,
				size_t size);
char			*get_prefix(t_prefix *prefix, char *s);
char			*get_param(char *param, char *s);
char			*get_command(char *command, char *s);

/*
**	output
*/

void			enqueue_write(t_server *server, void *client, void *ptr,
				size_t size);
void			enqueue_str_by_fd(t_env *env, int fd, char *s);

/*
**	receive functions
*/

void			recv_unknown(t_env *env, t_data *data, t_message *msg);
void			recv_nick(t_env *env, t_data *data, t_message *msg);
void			recv_user(t_env *env, t_data *data, t_message *msg);

/*
**	send functions
*/

void			send_error(t_env *env, t_data *data, char *error, char *comment);
void			send_welcome(t_env *env, t_data *data);

/*
**	verif functions
*/

t_bool			is_nickname_valid(char *nick);

#endif
