/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:54:30 by pribault          #+#    #+#             */
/*   Updated: 2018/04/02 19:04:45 by pribault         ###   ########.fr       */
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
# include "protocol.h"

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
	ERROR_ALLOCATION_RETURN
}				t_server_error;

/*
******************
**	structures  **
******************
*/

typedef struct	s_data
{
	void		*ptr;
	uint64_t	size;
	uint64_t	expected;
	char		name[NAME_MAX_LEN];
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
	t_protocol	protocol;
	t_domain	domain;
	t_vector	channels;
}				t_env;

typedef struct	s_command
{
	uint8_t		type;
	void		(*function)(t_env *, void *, void *, uint64_t);
	uint64_t	min_size;
	uint64_t	max_size;
}				t_command;

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

void			get_packet(t_env *env, void *client, t_header *ptr,
				uint64_t size);
void			handle_message(t_env *env, void *client, t_header *msg);

/*
**	output
*/

void			enqueue_str_by_fd(t_env *env, int fd, char *s);

#endif
