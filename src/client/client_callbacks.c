/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_callbacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:45:10 by pribault          #+#    #+#             */
/*   Updated: 2018/06/30 17:41:31 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_add(t_socket *socket, void *client)
{
	struct hostent	*host;
	t_data			data;
	t_env			*env;
	void			*ptr;

	env = socket_get_data(socket);
	ft_bzero(&data, sizeof(t_data));
	data.client = client;
	if ((host = gethostbyaddr(&client_get_address(client)->addr,
		client_get_address(client)->len, env->domain)))
		data.host = ft_strdup(host->h_name);
	if (!(ptr = ft_memdup(&data, sizeof(t_data))))
		ft_error(2, ERROR_ALLOCATION, NULL);
	client_attach_data(client, ptr);
	if (client_get_fd(client) != 0)
	{
		enqueue_str_by_fd(env, 1, ft_joinf("[%s] connected\n",
			inet_ntoa(*(struct in_addr *)&((struct sockaddr_in *)
				client_get_address(client))->sin_addr)));
		if (env->client)
			socket_remove_client(socket, env->client);
		env->client = client;
		send_nick(env->socket, env->client, env->username);
		send_user(env->socket, env->client, env->username, env->real_name);
	}
}

void	client_del(t_socket *socket, void *client)
{
	t_data	*data;
	t_env	*env;

	env = socket_get_data(socket);
	if (client_get_fd(client) != 0)
	{
		env->client = NULL;
		enqueue_str_by_fd(env, 1, ft_joinf("[%s] disconnected\n",
			inet_ntoa(*(struct in_addr *)&((struct sockaddr_in *)
				client_get_address(client))->sin_addr)));
	}
	else if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf("input disconnected\n"));
	data = client_get_data(client);
	if (data->host)
		free(data->host);
	if (data->ptr)
		free(data->ptr);
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
