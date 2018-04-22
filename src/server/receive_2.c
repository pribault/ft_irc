/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 18:39:44 by pribault          #+#    #+#             */
/*   Updated: 2018/04/22 23:38:44 by pribault         ###   ########.fr       */
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
		enqueue_str_by_fd(env, env->out, ft_joinf(
		"[%s%s!%s@%s%s (%s%s%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
		data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
		&msg->command, COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	server_remove_client(env->server, data->client);
}
