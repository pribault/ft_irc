/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_callbacks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:47:29 by pribault          #+#    #+#             */
/*   Updated: 2018/05/24 16:37:46 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	save_message(t_env *env, t_data *data, t_msg *msg)
{
	(void)env;
	if (!(data->ptr = realloc(data->ptr, data->size + msg->size)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	ft_memcpy(data->ptr + data->size, msg->ptr, msg->size);
	data->size += msg->size;
	msg->size = 0;
}

void	concatenate_messages(t_socket *socket, void *client, t_msg *msg)
{
	void	*save;
	void	*ptr;
	t_env	*env;
	t_data	*data;

	env = socket_get_data(socket);
	data = client_get_data(client);
	save_message(env, data, msg);
	while (data->ptr &&
		(ptr = ft_memschr(data->ptr, CRLF, data->size, CRLF_SIZE)))
	{
		treat_packet(socket, client, data->ptr, ptr - data->ptr);
		ft_memmove(data->ptr, ptr + CRLF_SIZE,
			data->size - (ptr - data->ptr) - CRLF_SIZE);
		save = data->ptr;
		if (!(data->ptr = realloc(data->ptr,
			data->size - (ptr - save) - CRLF_SIZE)) &&
			(data->size - (ptr - save) - CRLF_SIZE))
			ft_error(2, ERROR_ALLOCATION, NULL);
		data->size = data->size - (ptr - save) - CRLF_SIZE;
	}
}

void	message_received(t_socket *socket, void *client, t_msg *msg)
{
	t_env	*env;
	t_data	*data;
	void	*ptr;

	env = socket_get_data(socket);
	data = client_get_data(client);
	if (client_get_fd(client) == 0)
		return (get_user_command(env, msg->ptr, msg->size));
	while (msg->size)
		if (data->ptr)
			concatenate_messages(socket, client, msg);
		else if ((ptr = ft_memschr(msg->ptr, CRLF, msg->size, CRLF_SIZE)))
		{
			treat_packet(socket, client, msg->ptr, ptr - msg->ptr);
			msg->size -= ((ptr - msg->ptr) + CRLF_SIZE);
			msg->ptr = ptr + CRLF_SIZE;
		}
		else
			save_message(env, data, msg);
}

void	message_sended(t_socket *socket, void *client, t_msg *msg)
{
	t_env	*env;

	env = socket_get_data(socket);
	if (client_get_fd(client) != 2)
		free(msg->ptr);
	if (client_get_fd(client) != 1 && (env->opt & OPT_VERBOSE))
		enqueue_str_by_fd(env, 1, ft_joinf("[%s] message sended\n",
			inet_ntoa(*(struct in_addr *)&client_get_address(client)->addr)));
}

void	message_trashed(t_socket *socket, void *client, t_msg *msg)
{
	t_env	*env;

	(void)msg;
	env = socket_get_data(socket);
	if (client_get_fd(client) != 2)
		free(msg->ptr);
	ft_printf("[%sERROR%s] trashed\n", COLOR_ERROR, COLOR_CLEAR);
}
