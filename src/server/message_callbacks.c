/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_callbacks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 13:51:38 by pribault          #+#    #+#             */
/*   Updated: 2018/04/02 18:50:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	message_received(t_server *server, void *client, t_msg *msg)
{
	get_packet(server_get_data(server), client, msg->ptr,
		msg->size);
}

void	message_sended(t_server *server, void *client, t_msg *msg)
{
	t_env	*env;

	(void)msg;
	env = server_get_data(server);
	if (server_get_client_fd(client) == env->out)
		free(msg->ptr);
	else
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] message sended\n",
			inet_ntoa(*(struct in_addr *)server_get_client_address(client))));
}

void	message_trashed(t_server *server, void *client, t_msg *msg)
{
	t_env	*env;

	(void)msg;
	env = server_get_data(server);
	if (server_get_client_fd(client) == env->out)
		free(msg->ptr);
}
