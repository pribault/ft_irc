/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 18:39:44 by pribault          #+#    #+#             */
/*   Updated: 2018/05/24 16:43:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	recv_quit(t_env *env, t_data *data, t_message *msg)
{
	t_channel	*channel;
	uint64_t	i;
	uint64_t	j;

	i = (uint64_t)-1;
	while ((channel = ft_vector_get(&env->channels, ++i)))
		if (is_client_in_channel(channel, data) == FT_TRUE)
		{
			remove_client_from_channel(channel, data);
			j = (uint64_t)-1;
			while (ft_vector_get(&channel->clients, ++j))
				;
		}
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf(
		"[%s%s!%s@%s%s (%sQuit%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
		data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
		COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	socket_remove_client(env->socket, data->client);
}

void	recv_who(t_env *env, t_data *data, t_message *msg)
{
	size_t	i;

	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf(
		"[%s%s!%s@%s%s (%sWho%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
		data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
		COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	i = env->clients.n;
	while (--i != (size_t)-1)
		;
}

void	recv_ping(t_env *env, t_data *data, t_message *msg)
{
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf(
		"[%s%s!%s@%s%s (%sPing%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
		data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
		COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	send_pong(env, data);
}
