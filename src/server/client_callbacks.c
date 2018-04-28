/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_callbacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 12:28:02 by pribault          #+#    #+#             */
/*   Updated: 2018/04/28 20:15:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	client_add(t_socket *socket, void *client)
{
	struct hostent	*host;
	t_data			data;
	t_env			*env;

	env = socket_get_data(socket);
	ft_bzero(&data, sizeof(t_data));
	data.client = client;
	if ((host = gethostbyaddr(&client_get_address(client)->addr,
		client_get_address(client)->len, env->domain)))
		data.hostname = ft_strdup(host->h_name);
	client_attach_data(client, ft_memdup(&data, sizeof(t_data)));
	if (client_get_fd(client) != env->in)
	{
		ft_vector_add(&env->clients, &client);
		if (env->opt & OPT_VERBOSE)
			enqueue_str_by_fd(env, env->out, ft_joinf("[%s] connected\n",
			inet_ntoa(*(struct in_addr *)client_get_address(client))));
	}
}

void	client_del(t_socket *socket, void *client)
{
	t_data	*data;
	t_env	*env;

	data = client_get_data(client);
	env = socket_get_data(socket);
	if (client_get_fd(client) != env->in)
	{
		ft_vector_del_one(&env->clients,
			ft_vector_find(&env->clients, &client));
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] disconnected\n",
		inet_ntoa(*(struct in_addr *)client_get_address(client))));
	}
	if (data->hostname)
		free(data->hostname);
	if (data->username)
		free(data->username);
	free(data);
}

void	client_excpt(t_socket *socket, void *client)
{
	t_env	*env;

	env = socket_get_data(socket);
	if (client_get_fd(client) != env->in)
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] exception catched\n",
		inet_ntoa(*(struct in_addr *)client_get_address(client))));
	socket_remove_client(socket, client);
}
