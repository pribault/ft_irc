/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:48:20 by pribault          #+#    #+#             */
/*   Updated: 2018/04/07 21:26:30 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static t_cmd	g_commands[] =
{
	{PING, &command_ping},
	{NOTICE, &command_notice},
	{NULL, NULL},
};

void	command_ping(t_env *env, t_data *client, char *s)
{
	(void)s;
	send_pong(env->server, client->client);
}

void	command_notice(t_env *env, t_data *client, char *s)
{
	// enqueue_str_by_fd(env, env->out, ft_joinf("[%s] %s\n",
	// inet_ntoa(*(struct in_addr *)server_get_client_address(client->client)),
	// s));
}

void	treat_packet(t_server *server, void *client, void *ptr, size_t size)
{
	t_env		*env;
	t_data		*data;
	uint64_t	i;
	char		*s;

	env = server_get_data(server);
	data = server_client_get_data(client);
	if (!(s = malloc(size + 1)))
		return (ft_error(env->err, ERROR_ALLOCATION, NULL));
	ft_memcpy(s, ptr, size);
	s[size] = '\0';
	ft_printf("%s%s%s\n", COLOR_BOLD, s, COLOR_CLEAR);
	i = (uint64_t)-1;
	while (g_commands[++i].name)
		if (!ft_strncmp(s, g_commands[i].name, ft_strlen(g_commands[i].name)))
		{
			if (g_commands[i].function)
				return (g_commands[i].function(env, data, s));
			else
				return (ft_error(env->err, ERROR_UNHANDLE_PACKET,
					g_commands[i].name));
		}
	// ft_error(env->err, ERROR_UNKNOWN_PACKET, s);
	free(s);
}
