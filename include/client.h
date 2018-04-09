/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:59:09 by pribault          #+#    #+#             */
/*   Updated: 2018/04/09 09:00:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

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
# define COLOR_BLACK	COLOR(0, 0, 0)
# define COLOR_BLUE	COLOR(0, 51, 102)
# define COLOR_R1	COLOR(196, 64, 64)
# define COLOR_R2	COLOR(196, 0, 0)
# define COLOR_NAME	ft_get_term_color(COLOR_BLUE, COLOR_BLACK, EFFECT_NOBACK)
# define COLOR_WLCM	ft_get_term_color(COLOR_R1, COLOR_BLACK, EFFECT_NOBACK)
# define COLOR_YHST	ft_get_term_color(COLOR_R2, COLOR_BLACK, EFFECT_NOBACK)

/*
*************
**	enums  **
*************
*/

typedef enum	e_client_error
{
	ERROR_SETTING_DEFAULT = ERROR_FT_MAX,
	ERROR_UNKNOWN_PROTOCOL,
	ERROR_UNKNOWN_DOMAIN,
	ERROR_CANNOT_CONNECT,
	ERROR_SETUP_FDS,
	ERROR_UNHANDLE_PACKET,
	ERROR_UNKNOWN_PACKET
}				t_client_error;

/*
******************
**	structures  **
******************
*/

typedef struct	s_data
{
	void		*client;
	void		*ptr;
	size_t		size;
}				t_data;

typedef struct	s_env
{
	t_server	*server;
	void		*client;
	char		*address;
	char		*port;
	char		*username;
	char		*real_name;
	int			in;
	int			out;
	int			err;
	t_protocol	protocol;
	t_domain	domain;
}				t_env;

typedef struct	s_cmd
{
	char		*name;
	void		(*function)(t_env *, t_data *, t_message *);
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
**	packet functions
*/

void			treat_packet(t_server *server, void *client, void *ptr,
				size_t size);

/*
**	output functions
*/

void			enqueue_write(t_server *server, void *client, void *ptr,
				size_t size);
void			enqueue_str_by_fd(t_env *env, int fd, char *s);

/*
**	send functions
*/

void			send_nick(t_server *server, void *client, char *nick);
void			send_user(t_server *server, void *client, char *username,
				char *realname);
void			send_pong(t_server *server, void *client);

/*
**	receive functions
*/

void			recv_welcome(t_env *env, t_data *data, t_message *msg);
void			recv_yourhost(t_env *env, t_data *data, t_message *msg);

/*
**	command functions
*/

void			get_user_command(t_env *env, char *ptr, size_t size);
char			*get_prefix(t_prefix *prefix, char *s);
char			*get_command(char *command, char *s);
char			*get_param(char *param, char *s);

#endif
