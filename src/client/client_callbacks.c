/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_callbacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:45:10 by pribault          #+#    #+#             */
/*   Updated: 2018/04/02 18:46:15 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_add(t_server *server, void *client)
{
	(void)server;
	(void)client;
	ft_printf("client connected\n");
}

void	client_del(t_server *server, void *client)
{
	(void)server;
	(void)client;
	ft_printf("client disconnected\n");
}

void	client_excpt(t_server *server, void *client)
{
	server_remove_client(server, client);
	ft_printf("client exception\n");
}
