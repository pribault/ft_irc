/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_enqueue_write.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 09:45:27 by pribault          #+#    #+#             */
/*   Updated: 2018/04/11 21:59:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_enqueue_write(t_server *server, t_client *client,
		t_msg *msg)
{
	t_towrite	towrite;

	ft_memcpy(&towrite.client, client, sizeof(t_client));
	ft_memcpy(&towrite.data, msg, sizeof(t_msg));
	ft_circ_buffer_enqueue(&server->write_queue, &towrite);
	if (ft_circ_buffer_get_size(&server->write_queue) >=
		CIRCULAR_BUFFER_SIZE - 2 &&
		server->buffer_full)
		server->buffer_full(server);
}
