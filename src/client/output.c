/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:53:38 by pribault          #+#    #+#             */
/*   Updated: 2018/04/11 16:03:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	enqueue_write(t_server *server, void *client, void *ptr,
		size_t size)
{
	t_msg	msg;

	msg.ptr = ptr;
	msg.size = size;
	server_enqueue_write(server, client, &msg);
}

void	enqueue_str_by_fd(t_env *env, int fd, char *s)
{
	t_msg	msg;

	msg = (t_msg){s, ft_strlen(s)};
	server_enqueue_write_by_fd(env->server, fd, &msg);
}
