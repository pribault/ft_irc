/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_add_incoming_client.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:10:47 by pribault          #+#    #+#             */
/*   Updated: 2018/04/10 22:53:15 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_add_incoming_client(t_server *server, int *n_evts)
{
	struct hostent	*host;
	t_client		client;

	ft_bzero(&client, sizeof(t_client));
	client.addr.len = sizeof(struct sockaddr);
	if ((*n_evts) < 1 ||
		(client.fd = accept(server->sockfd, (void*)&client.addr,
		&client.addr.len)) < 0)
		return ;
	host = gethostbyaddr(&client.addr.addr, client.addr.len, server->domain);
	client.addr.str = ft_strdup(host->h_name);
	client.write_type = WRITE_BY_ADDR;
	(*n_evts)--;
	ft_vector_add(&server->clients, &client);
	if (server->client_add)
		server->client_add(server, ft_vector_get(&server->clients,
		server->clients.n - 1));
}
