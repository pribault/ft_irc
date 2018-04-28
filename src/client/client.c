/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:38:42 by pribault          #+#    #+#             */
/*   Updated: 2018/04/28 13:49:45 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static t_short_flag	g_short_flags[] =
{
	{'h', (void*)&print_usage},
	{'v', (void*)&set_verbose},
	{0, NULL}
};

static t_long_flag	g_long_flags[] =
{
	{"help", 0, {0}, (void*)&print_usage},
	{"protocol", 1, {PARAM_STR}, (void*)&get_protocol},
	{"domain", 1, {PARAM_STR}, (void*)&get_domain},
	{NULL, 0, {0}, NULL}
};

static t_error	g_errors[] =
{
	{ERROR_SETTING_DEFAULT, "'%s' address and port already set", 0},
	{ERROR_UNKNOWN_PROTOCOL, "unknown protocol '%s', allowed: tcp/udp", 0},
	{ERROR_UNKNOWN_DOMAIN, "unknown protocol '%s', allowed: ipv4/ipv6", 0},
	{ERROR_CANNOT_CONNECT, "cannot connect to %s", 0},
	{ERROR_SETUP_FDS, "cannot setup fds", ERROR_EXIT},
	{ERROR_UNHANDLE_PACKET, "unhandle packet type %s", 0},
	{ERROR_UNKNOWN_PACKET, "unknown packet received:\n%s", 0},
	{ERROR_UNKNOWN_COMMAND, "unknown command '%s'", 0},
	{ERROR_CORRUPTED_MEMORY, "memory is corrupted", ERROR_EXIT},
	{ERROR_DISCONNECTED, "you are not connected", 0},
	{0, NULL, 0}
};

void	socket_excpt(t_socket *socket)
{
	(void)socket;
	ft_printf("socket exception\n");
}

void	buffer_full(t_socket *socket)
{
	socket_poll_events(socket, ALLOW_WRITE);
}

int		init_env(t_env *env, int argc, char **argv)
{
	ft_add_errors((t_error*)&g_errors);
	env->address = NULL;
	env->port = NULL;
	env->protocol = TCP;
	env->domain = IPV4;
	env->client = NULL;
	env->opt = 0;
	ft_get_flags(argc, argv, ft_get_flag_array((void*)&g_short_flags,
		(void*)&g_long_flags, (void*)&get_default), env);
	if ((env->in = open("/dev/stdin", O_RDONLY)) == -1 ||
		(env->out = open("/dev/stdout", O_WRONLY)) == -1 ||
		(env->err = open("/dev/stderr", O_WRONLY)) == -1)
	{
		ft_error(2, ERROR_SETUP_FDS, NULL);
		return (0);
	}
	return (1);
}

void	start_socket(t_env *env)
{
	if (!(env->socket = socket_new()))
		ft_error(2, ERROR_ALLOCATION, NULL);
	socket_set_callback(env->socket, SOCKET_CLIENT_ADD_CB, &client_add);
	socket_set_callback(env->socket, SOCKET_CLIENT_DEL_CB, &client_del);
	socket_set_callback(env->socket, SOCKET_CLIENT_EXCEPTION_CB,
		&client_excpt);
	socket_set_callback(env->socket, SOCKET_EXCEPTION_CB,
		&socket_excpt);
	socket_set_callback(env->socket, SOCKET_MSG_RECV_CB, &message_received);
	socket_set_callback(env->socket, SOCKET_MSG_SEND_CB, &message_sended);
	socket_set_callback(env->socket, SOCKET_MSG_TRASH_CB, &message_trashed);
	socket_set_callback(env->socket, SOCKET_BUFFER_FULL_CB, &buffer_full);
	socket_attach_data(env->socket, env);
	socket_add_client_by_fd(env->socket, env->in);
}

int		main(int argc, char **argv)
{
	t_env	env;

	if (!init_env(&env, argc, argv) || !env.address || !env.port)
	{
		print_usage();
		return (1);
	}
	start_socket(&env);
	enqueue_str_by_fd(&env, env.out, ft_strdup("Enter your username:\n"));
	while (1)
	{
		if (check_malloc() != MALLOC_OK)
			ft_error(2, ERROR_CORRUPTED_MEMORY, NULL);
		socket_poll_events(env.socket, ACCEPT_CONNECTIONS | ALLOW_READ |
			ALLOW_WRITE);
	}
	return (0);
}
