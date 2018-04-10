/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:36:29 by pribault          #+#    #+#             */
/*   Updated: 2018/04/10 23:57:15 by pribault         ###   ########.fr       */
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

void	send_list(t_server *server, void *client)
{
	char	*s;

	if (!(s = ft_joinf("%s%s", LIST, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(server, client, s, ft_strlen(s));
}

void	send_join(t_server *server, void *client, char *list)
{
	char	**array;
	char	*s;

	if (!(array = ft_multisplit(list, WHITESPACES)) ||
		!(list = ft_implode(array, ',')) ||
		!(s = ft_joinf("%s %s%s", JOIN, list, CRLF)))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	free(list);
	ft_free_array((void**)array, ft_arraylen(array) + 1);
	enqueue_write(server, client, s, ft_strlen(s));
}
