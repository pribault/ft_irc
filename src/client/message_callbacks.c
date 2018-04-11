/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_callbacks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:47:29 by pribault          #+#    #+#             */
/*   Updated: 2018/04/11 13:45:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	concatenate_messages(t_server *server, void *client, t_msg *msg,
		void *ptr)
{
	t_env	*env;
	t_data	*data;

	env = server_get_data(server);
	data = server_client_get_data(client);
	if (!(data->ptr = realloc(data->ptr, data->size + ptr - msg->ptr)))
		ft_error(env->err, ERROR_ALLOCATION, NULL);
	ft_memcpy(data->ptr + data->size, msg->ptr, ptr - msg->ptr);
	treat_packet(server, client, data->ptr, data->size + ptr - msg->ptr);
	msg->size -= ((ptr - msg->ptr) + CRLF_SIZE);
	msg->ptr = ptr + CRLF_SIZE;
	ft_memdel(&data->ptr);
	data->size = 0;
}

void	save_message(t_env *env, t_data *data, t_msg *msg)
{
	if (!(data->ptr = realloc(data->ptr, data->size + msg->size)))
		ft_error(env->err, ERROR_ALLOCATION, NULL);
	ft_memcpy(data->ptr + data->size, msg->ptr, msg->size);
	data->size += msg->size;
	msg->size = 0;
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
		return (get_user_command(env, msg->ptr, msg->size));
	while (msg->size)
		if ((ptr = ft_memschr(msg->ptr, CRLF, msg->size, CRLF_SIZE)) &&
			ptr < msg->size + ptr - CRLF_SIZE)
		{
			if (data->ptr)
				concatenate_messages(server, client, msg, ptr);
			else
			{
				treat_packet(server, client, msg->ptr, ptr - msg->ptr);
				msg->size -= ((ptr - msg->ptr) + CRLF_SIZE);
				msg->ptr = ptr + CRLF_SIZE;
			}
		}
		else
			save_message(env, data, msg);
}

void	message_sended(t_server *server, void *client, t_msg *msg)
{
	t_env	*env;

	env = server_get_data(server);
	if (server_get_client_fd(client) != env->out && (env->opt & OPT_VERBOSE))
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] message sended\n",
			inet_ntoa(*(struct in_addr *)server_get_client_address(client))));
	if (server_get_client_fd(client) != env->err)
		free(msg->ptr);
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
