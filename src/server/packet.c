/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 11:18:20 by pribault          #+#    #+#             */
/*   Updated: 2018/04/08 14:23:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_cmd	g_commands[] =
{
	{PASS, &command_pass},
	{NICK, &command_nick},
	{USER, &command_user},
	{NULL, NULL},
};

void	command_pass(t_env *env, t_data *client, char *s)
{
	(void)env;
	(void)client;
	(void)s;
	ft_printf("nick\n");
}

void	command_nick(t_env *env, t_data *client, char *s)
{
	(void)env;
	(void)client;
	(void)s;
	ft_printf("nick\n");
}

void	command_user(t_env *env, t_data *client, char *s)
{
	(void)env;
	(void)client;
	(void)s;
	ft_printf("user\n");
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
	ft_printf("%s\n", s);
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
	ft_error(env->err, ERROR_UNKNOWN_PACKET, s);
	free(s);
}
