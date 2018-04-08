/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:38:42 by pribault          #+#    #+#             */
/*   Updated: 2018/04/08 11:47:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static t_short_flag	g_short_flags[] =
{
	{'h', (void*)&print_usage},
	{0, NULL}
};

static t_long_flag	g_long_flags[] =
{
	{"help", 0, {0}, (void*)&print_usage},
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
	{0, NULL, 0}
};

void	server_excpt(t_server *server)
{
	(void)server;
	ft_printf("server exception\n");
}

int		init_env(t_env *env, int argc, char **argv)
{
	ft_add_errors((t_error*)&g_errors);
	env->address = NULL;
	env->port = NULL;
	env->protocol = TCP;
	env->domain = IPV4;
	env->client = NULL;
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

void	start_server(t_env *env)
{
	if (!(env->server = server_new()))
		ft_error(2, ERROR_ALLOCATION, NULL);
	server_set_callback(env->server, SERVER_CLIENT_ADD_CB, &client_add);
	server_set_callback(env->server, SERVER_CLIENT_DEL_CB, &client_del);
	server_set_callback(env->server, SERVER_CLIENT_EXCEPTION_CB,
		&client_excpt);
	server_set_callback(env->server, SERVER_SERVER_EXCEPTION_CB,
		&server_excpt);
	server_set_callback(env->server, SERVER_MSG_RECV_CB, &message_received);
	server_set_callback(env->server, SERVER_MSG_SEND_CB, &message_sended);
	server_set_callback(env->server, SERVER_MSG_TRASH_CB, &message_trashed);
	server_attach_data(env->server, env);
	server_add_client_by_fd(env->server, env->in);
}

int		main(int argc, char **argv)
{
	t_env	env;

	if (!init_env(&env, argc, argv) || !env.address || !env.port)
	{
		print_usage();
		return (1);
	}
	start_server(&env);
	enqueue_str_by_fd(&env, env.out, ft_strdup("Enter your username:\n"));
	while (1)
		server_poll_events(env.server);
	return (0);
}
