/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:53:38 by pribault          #+#    #+#             */
/*   Updated: 2018/04/28 13:56:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	enqueue_write(t_socket *socket, void *client, void *ptr,
		size_t size)
{
	t_msg	msg;

	msg.ptr = ptr;
	msg.size = size;
	socket_enqueue_write(socket, client, &msg);
}

void	enqueue_str_by_fd(t_env *env, int fd, char *s)
{
	t_msg	msg;

	msg = (t_msg){s, ft_strlen(s)};
	socket_enqueue_write_by_fd(env->socket, fd, &msg);
}
