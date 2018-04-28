/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 22:14:50 by pribault          #+#    #+#             */
/*   Updated: 2018/04/28 19:27:58 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_listend(t_env *env, t_data *data)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s :%s%s", &data->nickname,
		RPL_LISTEND, "end of channel list",
		CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_pong(t_env *env, t_data *data)
{
	char	*s;

	if (!(s = ft_joinf("%s%s", PONG, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}
