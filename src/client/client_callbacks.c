/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_callbacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:45:10 by pribault          #+#    #+#             */
/*   Updated: 2018/04/07 17:13:16 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_add(t_server *server, void *client)
{
	t_data	data;
	t_env	*env;

	env = server_get_data(server);
	ft_bzero(&data, sizeof(t_data));
	data.client = client;
	server_client_attach_data(client, ft_memdup(&data, sizeof(t_data)));
	if (server_get_client_fd(client) != env->in)
	{
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] connected\n",
		inet_ntoa(*(struct in_addr *)server_get_client_address(client))));
		send_nick(server, client, "pribault");
		send_user(server, client);
	}
}

void	client_del(t_server *server, void *client)
{
	t_env	*env;

	env = server_get_data(server);
	if (server_get_client_fd(client) != env->in)
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] disconnected\n",
		inet_ntoa(*(struct in_addr *)server_get_client_address(client))));
	free(server_client_get_data(client));
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
