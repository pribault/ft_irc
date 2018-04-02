/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_packet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 16:38:31 by pribault          #+#    #+#             */
/*   Updated: 2018/04/02 19:00:23 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	message_notification(t_env *env, void *client, uint64_t size,
			uint64_t expected)
{
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, env->out, ft_joinf("[%s] %u/%u\n",
			inet_ntoa(*(struct in_addr *)server_get_client_address(client)),
			size, expected));
}

static void	save_message(t_env *env, void *client, t_header *ptr,
			uint64_t size)
{
	t_data	*data;

	data = server_client_get_data(client);
	if (!data->ptr)
	{
		if (!(data->ptr = malloc(sizeof(t_header) + ptr->size)))
			return (ft_error(2, ERROR_ALLOCATION_RETURN, NULL));
		ft_memcpy(data->ptr, ptr, size);
		data->expected = ptr->size;
		data->size = size;
	}
	else if (data->size + size >= data->expected)
	{
		ft_memcpy(data->ptr + data->size, ptr,
		data->expected - data->size);
	}
	else
	{
		ft_memcpy(data->ptr + data->size, ptr, size);
		data->size += size;
	}
	message_notification(env, client, data->size, data->expected);
}

static void	message_complete(t_env *env, void *client, t_header *ptr)
{
	t_data	*data;

	data = server_client_get_data(client);
	message_notification(env, client, ptr->size, ptr->size);
	handle_message(env, client, ptr);
	if (data->ptr)
		ft_memdel(&data->ptr);
}

static void	waiting_for_message(t_env *env, void *client, t_header *ptr,
			uint64_t size)
{
	t_data		*data;
	uint64_t	save;

	data = server_client_get_data(client);
	if (data->size + size >= data->expected)
	{
		save = data->expected - data->size;
		save_message(env, client, ptr, size);
		message_complete(env, client, data->ptr);
		get_packet(env, client, (void*)ptr + save, size - save);
	}
	else
		save_message(env, client, ptr, size);
}

void		get_packet(t_env *env, void *client, t_header *ptr,
			uint64_t size)
{
	t_data	*data;

	data = server_client_get_data(client);
	if (data->ptr)
		waiting_for_message(env, client, ptr, size);
	else if (size >= sizeof(t_header))
	{
		if (ptr->size <= size)
		{
			message_complete(env, client, ptr);
			get_packet(env, client, (void*)ptr + ptr->size,
			size - ptr->size);
		}
		else
			save_message(env, client, ptr, size);
	}
	else if (size)
		ft_error(2, ERROR_PACKET_TOO_SMALL, NULL);
}
