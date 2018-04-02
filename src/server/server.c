/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:38:44 by pribault          #+#    #+#             */
/*   Updated: 2018/04/02 19:06:22 by pribault         ###   ########.fr       */
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
	{0, NULL, 0}
};

void	server_excpt(t_server *server)
{
	(void)server;
	ft_printf("server exception\n");
}

int		init_env(t_env *env, int argc, char **argv)
{
	ft_bzero(env, sizeof(t_env));
	ft_add_errors((t_error*)&g_errors);
	env->port = NULL;
	env->protocol = TCP;
	env->domain = IPV4;
	ft_get_flags(argc, argv, ft_get_flag_array((void*)&g_short_flags,
		(void*)&g_long_flags, (void*)&get_default), env);
	if (!(env->in = open("/dev/stdin", O_RDONLY)))
	{
		ft_error(2, ERROR_FILE, "/dev/stdin");
		return (0);
	}
	if (!(env->out = open("/dev/stdout", O_WRONLY)))
	{
		ft_error(2, ERROR_FILE, "/dev/stdout");
		return (0);
	}
	return (1);
}

void	start_server(t_env *env)
{
	if (!(env->server = server_new()))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	server_set_callback(env->server, SERVER_CLIENT_ADD_CB, &client_add);
	server_set_callback(env->server, SERVER_CLIENT_DEL_CB, &client_del);
	server_set_callback(env->server, SERVER_CLIENT_EXCEPTION_CB, &client_excpt);
	server_set_callback(env->server, SERVER_SERVER_EXCEPTION_CB, &server_excpt);
	server_set_callback(env->server, SERVER_MSG_RECV_CB, &message_received);
	server_set_callback(env->server, SERVER_MSG_SEND_CB, &message_sended);
	server_set_callback(env->server, SERVER_MSG_TRASH_CB, &message_trashed);
	server_attach_data(env->server, env);
	server_start(env->server, (t_method){TCP, IPV4}, env->port);
	server_add_client_by_fd(env->server, env->in);
	ft_vector_init(&env->channels, sizeof(t_channel*), 0);
}

int		main(int argc, char **argv)
{
	t_env	env;

	if (!init_env(&env, argc, argv) || !env.port)
	{
		print_usage();
		return (1);
	}
	start_server(&env);
	while (1)
		server_poll_events(env.server);
	return (0);
}
