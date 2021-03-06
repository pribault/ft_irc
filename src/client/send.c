/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:36:29 by pribault          #+#    #+#             */
/*   Updated: 2018/05/24 11:13:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_nick(t_socket *socket, void *client, char *nick)
{
	char	*s;

	if (!(s = ft_joinf("%s %s%s", NICK, nick, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(socket, client, s, ft_strlen(s));
}

void	send_user(t_socket *socket, void *client,
		char *username, char *realname)
{
	char	*s;

	if (!(s = ft_joinf("%s %s 0 * :%s%s", USER, username, realname, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(socket, client, s, ft_strlen(s));
}

void	send_pong(t_socket *socket, void *client)
{
	t_env	*env;
	char	*s;

	env = socket_get_data(socket);
	if (!(s = ft_joinf("%s %s%s", PONG, env->username, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(socket, client, s, ft_strlen(s));
}

void	send_list(t_socket *socket, void *client)
{
	char	*s;

	if (!(s = ft_joinf("%s%s", LIST, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(socket, client, s, ft_strlen(s));
}
