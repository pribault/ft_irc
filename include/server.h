/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:54:30 by pribault          #+#    #+#             */
/*   Updated: 2018/04/07 19:22:40 by pribault         ###   ########.fr       */
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

# define COLOR_BOLD			"\e[1m"
# define COLOR_HALF			"\e[2m"
# define COLOR_ITALIC		"\e[3m"
# define COLOR_UNDERLINED	"\e[4m"
# define COLOR_CLEAR		"\e[0m"

# define OPT_VERBOSE		BYTE(0)

# define NAME_MAX_LEN		10

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
	ERROR_SETUP_FDS
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
	char		nick[NAME_MAX_LEN];
	t_vector	channels;
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
}				t_env;

typedef struct	s_cmd
{
	char		*name;
	void		(*function)(t_env *, t_data *, char *);
}				t_cmd;

/*
******************
**	prototypes  **
******************
*/

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
void			command_pass(t_env *env, t_data *client, char *s);
void			command_nick(t_env *env, t_data *client, char *s);
void			command_user(t_env *env, t_data *client, char *s);

/*
**	output
*/

void			enqueue_response(t_server *server, void *client,
				char *response);
void			enqueue_write(t_server *server, void *client, void *ptr,
				size_t size);
void			enqueue_str_by_fd(t_env *env, int fd, char *s);

#endif
