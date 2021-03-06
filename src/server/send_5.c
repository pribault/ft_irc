/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 16:58:36 by pribault          #+#    #+#             */
/*   Updated: 2018/08/25 16:26:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_no_such_nick(t_env *env, t_data *data, char *name)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s %s :No such nick/channel%s", env->name,
		ERR_NOSUCHNICK, name, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_ping(t_env *env, t_data *data)
{
	char	*s;

	if (!(s = ft_joinf("%s :%s%s", PING, env->name, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_part(t_env *env, t_data *data, t_data *to, t_channel *channel)
{
	char	*s;

	if (!(s = ft_joinf(":%s!%s~%s %s %s :%s", data->nickname, data->username,
		data->hostname, PART, channel->name, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, to->client, s, ft_strlen(s));
}
