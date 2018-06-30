/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_callbacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 12:28:02 by pribault          #+#    #+#             */
/*   Updated: 2018/06/30 19:10:28 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	notify_disconnection(t_env *env, t_data *data, char *reason)
{
	t_channel	*channel;
	t_data		**client;
	size_t		i;
	size_t		j;

	i = (size_t)-1;
	while (++i < env->channels.n &&
		(channel = ft_vector_get(&env->channels, i)))
		if (is_client_in_channel(channel, data))
		{
			j = (size_t)-1;
			while (++j < channel->clients.n &&
				(client = ft_vector_get(&channel->clients, j)))
				if (data != *client)
					send_quit(env, data, *client, reason);
			remove_client_from_channel(channel, data);
			if (!channel->clients.n)
				ft_vector_del_one(&env->channels, i--);
		}
}

void	client_add(t_socket *socket, void *client)
{
	t_data			data;
	t_env			*env;

	env = socket_get_data(socket);
	ft_bzero(&data, sizeof(t_data));
	data.client = client;
	data.hostname = client_get_address(client)->str;
	data.last = env->now;
	client_attach_data(client, ft_memdup(&data, sizeof(t_data)));
	if (client_get_fd(client) != 0)
	{
		ft_vector_add(&env->clients, &client);
		if (env->opt & OPT_VERBOSE)
			enqueue_str_by_fd(env, 1, ft_joinf("[%s] connected\n",
			inet_ntoa(*(struct in_addr *)&((struct sockaddr_in *)
				client_get_address(client))->sin_addr)));
	}
}

void	client_del(t_socket *socket, void *client)
{
	t_data	*data;
	t_env	*env;

	data = client_get_data(client);
	env = socket_get_data(socket);
	notify_disconnection(env, data, "an undefined reason");
	if (client_get_fd(client) != 0)
	{
		ft_vector_del_one(&env->clients,
		ft_vector_find(&env->clients, &client));
		if (env->opt & OPT_VERBOSE)
			enqueue_str_by_fd(env, 1, ft_joinf("[%s] disconnected\n",
			inet_ntoa(*(struct in_addr *)&((struct sockaddr_in *)
				client_get_address(client))->sin_addr)));
	}
	if (data->username)
		free(data->username);
	if (data->realname)
		free(data->realname);
	free(data);
}

void	client_excpt(t_socket *socket, void *client)
{
	t_env	*env;

	env = socket_get_data(socket);
	if (client_get_fd(client) != 0)
		enqueue_str_by_fd(env, 1, ft_joinf("[%s] exception catched\n",
		inet_ntoa(*(struct in_addr *)&((struct sockaddr_in *)
			client_get_address(client))->sin_addr)));
	socket_remove_client(socket, client);
}
