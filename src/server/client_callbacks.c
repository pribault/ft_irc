/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_callbacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 12:28:02 by pribault          #+#    #+#             */
/*   Updated: 2018/04/21 22:38:49 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	client_add(t_server *server, void *client)
{
	t_data	data;
	t_env	*env;

	env = server_get_data(server);
	ft_bzero(&data, sizeof(t_data));
	data.client = client;
	data.hostname = server_get_client_address(client)->str;
	server_client_attach_data(client, ft_memdup(&data, sizeof(t_data)));
	if (server_get_client_fd(client) != env->in)
	{
		ft_vector_add(&env->clients, &client);
		if (env->opt & OPT_VERBOSE)
			enqueue_str_by_fd(env, env->out, ft_joinf("[%s] connected\n",
			inet_ntoa(*(struct in_addr *)server_get_client_address(client))));
	}
}

void	client_del(t_server *server, void *client)
{
	t_data	*data;
	t_env	*env;

	data = server_client_get_data(client);
	env = server_get_data(server);
	if (server_get_client_fd(client) != env->in)
	{
		ft_vector_del_one(&env->clients,
			ft_vector_find(&env->clients, &client));
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] disconnected\n",
		inet_ntoa(*(struct in_addr *)server_get_client_address(client))));
	}
	if (data->username)
		free(data->username);
	free(data);
}

void	client_excpt(t_server *server, void *client)
{
	t_env	*env;

	env = server_get_data(server);
	if (server_get_client_fd(client) != env->in)
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] exception catched\n",
		inet_ntoa(*(struct in_addr *)server_get_client_address(client))));
	server_remove_client(server, client);
}
