/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 17:12:03 by pribault          #+#    #+#             */
/*   Updated: 2018/04/28 13:56:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_join(t_socket *socket, void *client, char *list)
{
	char	**array;
	char	*s;

	if (!(array = ft_multisplit(list, WHITESPACES)) ||
		!(list = ft_implode(array, ',')) ||
		!(s = ft_joinf("%s %s%s", JOIN, list, CRLF)))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	free(list);
	ft_free_array((void**)array, ft_arraylen(array) + 1);
	enqueue_write(socket, client, s, ft_strlen(s));
}

void	send_quit(t_socket *socket, void *client, char *comment)
{
	char	*s;

	if (!(s = ft_joinf("%s :%s%s", QUIT, comment, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(socket, client, s, ft_strlen(s));
}
