/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:36:29 by pribault          #+#    #+#             */
/*   Updated: 2018/04/08 12:00:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_nick(t_server *server, void *client, char *nick)
{
	char	*s;

	if (!(s = ft_joinf("%s %s%s", NICK, nick, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(server, client, s, ft_strlen(s));
}

void	send_user(t_server *server, void *client,
		char *username, char *realname)
{
	char	*s;

	if (!(s = ft_joinf("%s %s 0 * :%s%s", USER, username, realname, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(server, client, s, ft_strlen(s));
}

void	send_pong(t_server *server, void *client)
{
	char	*s;

	if (!(s = ft_joinf("%s%s", PONG, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(server, client, s, ft_strlen(s));
}
