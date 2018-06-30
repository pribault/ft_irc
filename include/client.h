/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:59:09 by pribault          #+#    #+#             */
/*   Updated: 2018/06/30 12:42:00 by pribault         ###   ########.fr       */
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

# define OPT_VERBOSE	BYTE(0)

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
# define COLOR_M0		"\e[38;5;203m"
# define COLOR_ERROR	COLOR_R0
# define COLOR_SYSTEM	COLOR_M0
# define COLOR_INFO		COLOR_Y0
# define COLOR_MESSAGE	COLOR_C0
# define COLOR_VERBOSE	COLOR_G0
# define COLOR_NAME		COLOR_B0

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
	ERROR_UNKNOWN_PACKET,
	ERROR_UNKNOWN_COMMAND,
	ERROR_CORRUPTED_MEMORY,
	ERROR_DISCONNECTED,
	ERROR_ALREADY_CONNECTED,
	ERROR_INVALID_PARAMETERS
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
	char		*host;
}				t_data;

typedef struct	s_env
{
	t_socket	*socket;
	void		*client;
	char		*address;
	char		*port;
	char		*username;
	char		*real_name;
	uint32_t	opt;
	t_protocol	protocol;
	t_domain	domain;
	t_bool		connected;
}				t_env;

typedef struct	s_cmd
{
	char		*name;
	void		(*function)(t_env *, t_data *, t_message *);
}				t_cmd;

typedef struct	s_user_cmd
{
	char		*name;
	void		(*function)(t_env *, char *);
}				t_user_cmd;

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
**	packet functions
*/

void			treat_packet(t_socket *socket, void *client, void *ptr,
				size_t size);

/*
**	output functions
*/

void			enqueue_write(t_socket *socket, void *client, void *ptr,
				size_t size);
void			enqueue_str_by_fd(t_env *env, int fd, char *s);

/*
**	send functions
*/

void			send_nick(t_socket *socket, void *client, char *nick);
void			send_user(t_socket *socket, void *client, char *username,
				char *realname);
void			send_pong(t_socket *socket, void *client);
void			send_list(t_socket *socket, void *client);
void			send_join(t_socket *socket, void *client, char *list);
void			send_quit(t_socket *socket, void *client, char *comment);
void			send_who(t_socket *socket, void *client, char *str,
				char *comment);

/*
**	receive functions
*/

void			recv_unknown(t_env *env, t_data *data, t_message *msg);
void			recv_welcome(t_env *env, t_data *data, t_message *msg);
void			recv_yourhost(t_env *env, t_data *data, t_message *msg);
void			recv_created(t_env *env, t_data *data, t_message *msg);
void			recv_myinfo(t_env *env, t_data *data, t_message *msg);
void			recv_bounce(t_env *env, t_data *data, t_message *msg);
void			recv_notice(t_env *env, t_data *data, t_message *msg);
void			recv_lusers(t_env *env, t_data *data, t_message *msg);
void			recv_lops(t_env *env, t_data *data, t_message *msg);
void			recv_motdstart(t_env *env, t_data *data, t_message *msg);
void			recv_motd(t_env *env, t_data *data, t_message *msg);
void			recv_motdend(t_env *env, t_data *data, t_message *msg);
void			recv_lchannels(t_env *env, t_data *data, t_message *msg);
void			recv_lme(t_env *env, t_data *data, t_message *msg);
void			recv_mode(t_env *env, t_data *data, t_message *msg);
void			recv_nick(t_env *env, t_data *data, t_message *msg);
void			recv_liststart(t_env *env, t_data *data, t_message *msg);
void			recv_list(t_env *env, t_data *data, t_message *msg);
void			recv_listend(t_env *env, t_data *data, t_message *msg);
void			recv_localusers(t_env *env, t_data *data, t_message *msg);
void			recv_globalusers(t_env *env, t_data *data, t_message *msg);
void			recv_join(t_env *env, t_data *data, t_message *msg);
void			recv_ping(t_env *env, t_data *data, t_message *msg);
void			recv_userunknown(t_env *env, t_data *data, t_message *msg);
void			recv_quit(t_env *env, t_data *data, t_message *msg);
void			recv_who_reply(t_env *env, t_data *data, t_message *msg);
void			recv_end_of_who(t_env *env, t_data *data, t_message *msg);
void			recv_err_no_such_server(t_env *env, t_data *data,
				t_message *msg);

void			recv_error(t_env *env, t_data *data, t_message *msg);

/*
**	command functions
*/

void			get_user_command(t_env *env, char *ptr, size_t size);
void			cmd_nick(t_env *env, char *s);
void			cmd_list(t_env *env, char *s);
void			cmd_join(t_env *env, char *s);
void			cmd_quit(t_env *env, char *s);
void			cmd_who(t_env *env, char *s);
void			cmd_connect(t_env *env, char *s);
void			cmd_help(t_env *env, char *s);

char			*get_prefix(t_prefix *prefix, char *s);
char			*get_command(char *command, char *s);
char			*get_param(char *param, char *s);

#endif
