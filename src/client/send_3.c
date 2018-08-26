/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 15:41:10 by pribault          #+#    #+#             */
/*   Updated: 2018/08/25 15:43:45 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_leave(t_socket *socket, void *client, char *list)
{
	char	**array;
	char	*s;

	if (!(array = ft_multisplit(list, WHITESPACES)) ||
		!(list = ft_implode(array, ',')) ||
		!(s = ft_joinf("%s %s%s", PART, list, CRLF)))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	free(list);
	ft_free_array((void**)array, ft_arraylen(array) + 1);
	enqueue_write(socket, client, s, ft_strlen(s));
}
