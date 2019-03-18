/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:38:44 by pribault          #+#    #+#             */
/*   Updated: 2018/08/25 15:17:07 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_short_flag	g_short_flags[] =
{
	{'h', (void*)&print_usage},
	{'v', (void*)set_verbose},
	{0, NULL}
};

static t_long_flag	g_long_flags[] =
{
	{"help", 0, {0}, (void*)&print_usage},
	{"verbose", 0, {0}, (void*)&set_verbose},
	{"protocol", 1, {PARAM_STR}, (void*)&get_protocol},
	{"domain", 1, {PARAM_STR}, (void*)&get_domain},
	{NULL, 0, {0}, NULL}
};

static t_error	g_errors[] =
{
	{ERROR_SETTING_DEFAULT, "'%s' port already set", 0},
	{ERROR_UNKNOWN_PROTOCOL, "unknown protocol '%s', allowed: tcp/udp", 0},
	{ERROR_UNKNOWN_DOMAIN, "unknown protocol '%s', allowed: ipv4/ipv6", 0},
	{ERROR_PACKET_TOO_SMALL, "packet received too small to contain header", 0},
	{ERROR_ALLOCATION_RETURN, "cannot allocate memory", 0},
	{ERROR_UNHANDLE_PACKET, "unhandle packet type %s", 0},
	{ERROR_UNKNOWN_PACKET, "unknown packet received:\n%s", 0},
	{ERROR_SETUP_FDS, "cannot setup fds", ERROR_EXIT},
	{ERROR_LOADING_CONFIG, "cannot load config", ERROR_EXIT},
	{ERROR_PORT_PARAMS, "'%u' PORT take two parameters", 0},
	{ERROR_SERVNAME_PARAMS, "'%u' SERVNAME take two parameters", 0},
	{ERROR_MOTD_PARAMS, "'%u' MOTD take two parameters", 0},
	{ERROR_CANNOT_START, "cannot start socket on port %s", ERROR_EXIT},
	{ERROR_CORRUPTED_MEMORY, "memory is corrupted", ERROR_EXIT},
	{0, NULL, 0}
};

void	socket_excpt(t_socket *socket)
{
	(void)socket;
	ft_printf("socket exception\n");
}

void	buffer_full(t_socket *socket)
{
	static uint32_t	n = 0;

	n++;
	ft_printf("n=%u\n", n);
	socket_poll_events(socket, ALLOW_WRITE);
	n--;
}

int		init_env(t_env *env, int argc, char **argv)
{
	ft_bzero(env, sizeof(t_env));
	ft_add_errors((t_error*)&g_errors);
	env->port = NULL;
	env->protocol = TCP;
	env->domain = IPV4;
	ft_vector_init(&env->clients, ALLOC_MALLOC, sizeof(void **));
	ft_vector_init(&env->channels, ALLOC_MALLOC, sizeof(t_channel));
	if (!load_config(env))
		ft_error(2, ERROR_LOADING_CONFIG, NULL);
	ft_get_flags(argc, argv, ft_get_flag_array((void*)&g_short_flags,
		(void*)&g_long_flags, (void*)&get_default), env);
	return (1);
}

void	start_socket(t_env *env)
{
	if (!(env->socket = socket_new()))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
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
	if (!socket_bind(env->socket, (t_method){env->protocol, IPV4}, env->port))
		ft_error(2, ERROR_CANNOT_START, env->port);
	socket_add_client_by_fd(env->socket, 0);
}

int		main(int argc, char **argv)
{
	t_env	env;

	if (!init_env(&env, argc, argv) || !env.port)
	{
		print_usage();
		return (1);
	}
	start_socket(&env);
	while (1)
	{
		gettimeofday(&env.now, NULL);
		check_clients_activity(&env);
		socket_poll_events(env.socket, ACCEPT_CONNECTIONS | ALLOW_READ |
			ALLOW_WRITE);
	}
	return (0);
}
