/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_callbacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:45:10 by pribault          #+#    #+#             */
/*   Updated: 2018/04/11 13:33:15 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_add(t_server *server, void *client)
{
	t_data	data;
	t_env	*env;
	void	*ptr;

	env = server_get_data(server);
	ft_bzero(&data, sizeof(t_data));
	data.client = client;
	if (!(ptr = ft_memdup(&data, sizeof(t_data))))
		ft_error(2, ERROR_ALLOCATION, NULL);
	server_client_attach_data(client, ptr);
	if (server_get_client_fd(client) != env->in &&
		server_get_client_fd(client) != 0)
	{
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] connected\n",
		inet_ntoa(*(struct in_addr *)server_get_client_address(client))));
		if (env->client)
			server_remove_client(server, env->client);
		env->client = client;
		send_nick(env->server, env->client, env->username);
		send_user(env->server, env->client, env->username, env->real_name);
	}
}

void	client_del(t_server *server, void *client)
{
	t_data	*data;
	t_env	*env;

	env = server_get_data(server);
	if (server_get_client_fd(client) != env->in &&
		server_get_client_fd(client) != 0)
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] disconnected\n",
		inet_ntoa(*(struct in_addr *)server_get_client_address(client))));
	data = server_client_get_data(client);
	if (data->ptr)
		free(data->ptr);
	free(data);
}

void	client_excpt(t_server *server, void *client)
{
	t_env	*env;

	env = server_get_data(server);
	if (server_get_client_fd(client) != env->in &&
		server_get_client_fd(client) != 0)
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] exception catched\n",
		inet_ntoa(*(struct in_addr *)server_get_client_address(client))));
	server_remove_client(server, client);
}
