/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 17:10:30 by pribault          #+#    #+#             */
/*   Updated: 2018/04/07 13:35:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	enqueue_response(t_server *server, void *client, char *response)
{
	t_msg	msg;

	msg.ptr = response;
	msg.size = ft_strlen(response);
	server_enqueue_write(server, client, &msg);
	msg.ptr = CRLF;
	msg.size = CRLF_SIZE;
	server_enqueue_write(server, client, &msg);
}

void	enqueue_str_by_fd(t_env *env, int fd, char *s)
{
	t_msg	msg;

	msg = (t_msg){s, ft_strlen(s)};
	server_enqueue_write_by_fd(env->server, fd, &msg);
}
