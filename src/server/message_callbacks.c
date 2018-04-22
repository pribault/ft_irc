/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_callbacks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 13:51:38 by pribault          #+#    #+#             */
/*   Updated: 2018/04/22 16:10:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	save_message(t_env *env, t_data *data, t_msg *msg)
{
	if (!(data->ptr = realloc(data->ptr, data->size + msg->size)))
		ft_error(env->err, ERROR_ALLOCATION, NULL);
	ft_memcpy(data->ptr + data->size, msg->ptr, msg->size);
	data->size += msg->size;
	msg->size = 0;
}

void	concatenate_messages(t_server *server, void *client, t_msg *msg)
{
	void	*save;
	void	*ptr;
	t_env	*env;
	t_data	*data;

	env = server_get_data(server);
	data = server_client_get_data(client);
	save_message(env, data, msg);
	while (data->ptr &&
		(ptr = ft_memschr(data->ptr, CRLF, data->size, CRLF_SIZE)))
	{
		treat_packet(server, client, data->ptr, ptr - data->ptr);
		ft_memmove(data->ptr, ptr + CRLF_SIZE,
			data->size - (ptr - data->ptr) - CRLF_SIZE);
		save = data->ptr;
		if (!(data->ptr = realloc(data->ptr,
			data->size - (ptr - data->ptr) - CRLF_SIZE)) &&
			(data->size - (ptr - save) - CRLF_SIZE))
			ft_error(2, ERROR_ALLOCATION, NULL);
		data->size = data->size - (ptr - save) - CRLF_SIZE;
	}
}

void	message_received(t_server *server, void *client, t_msg *msg)
{
	t_env	*env;
	t_data	*data;
	void	*ptr;

	env = server_get_data(server);
	data = server_client_get_data(client);
	if (server_get_client_fd(client) == env->in ||
		server_get_client_fd(client) == 0)
		return ;
	while (msg->size)
		if (data->ptr)
			concatenate_messages(server, client, msg);
		else if ((ptr = ft_memschr(msg->ptr, CRLF, msg->size, CRLF_SIZE)))
		{
			treat_packet(server, client, msg->ptr, ptr - msg->ptr);
			msg->size -= ((ptr - msg->ptr) + CRLF_SIZE);
			msg->ptr = ptr + CRLF_SIZE;
		}
		else
			save_message(env, data, msg);
}

void	message_sended(t_server *server, void *client, t_msg *msg)
{
	t_env	*env;

	env = server_get_data(server);
	if (server_get_client_fd(client) != env->err)
		free(msg->ptr);
	if (server_get_client_fd(client) != env->out && (env->opt & OPT_VERBOSE))
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] message sended\n",
			inet_ntoa(*(struct in_addr *)server_get_client_address(client))));
}

void	message_trashed(t_server *server, void *client, t_msg *msg)
{
	t_env	*env;

	(void)msg;
	env = server_get_data(server);
	if (server_get_client_fd(client) != env->err)
		free(msg->ptr);
	ft_printf("[%sERROR%s] trashed\n", COLOR_ERROR, COLOR_CLEAR);
}
