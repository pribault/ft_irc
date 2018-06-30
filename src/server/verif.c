/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:00:47 by pribault          #+#    #+#             */
/*   Updated: 2018/06/30 20:08:18 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_bool	is_nickname_valid(char *nick)
{
	uint32_t	i;

	if (!ft_isof(nick[0], PARAM_LETTERS) &&
		!ft_isof(nick[0], PARAM_SPECIAL))
		return (FT_FALSE);
	i = 0;
	while (++i < NICK_MAX_LEN && nick[i])
		if (!ft_isof(nick[i], PARAM_LETTERS) &&
			!ft_isof(nick[i], PARAM_SPECIAL) &&
			!ft_isof(nick[i], PARAM_NUMBER) &&
			nick[i] != '-')
			return (FT_FALSE);
	if (nick[i])
		return (FT_FALSE);
	return (FT_TRUE);
}

void	check_clients_activity(t_env *env)
{
	t_data	*data;
	size_t	diff;
	size_t	i;

	i = (size_t)-1;
	while (++i < env->clients.n &&
		(data = client_get_data(*(void **)ft_vector_get(&env->clients, i))))
	{
		diff = (env->now.tv_sec - data->last.tv_sec) +
			(env->now.tv_usec - data->last.tv_usec) / 1000000;
		if (diff >= TIMEOUT_PONG)
			socket_remove_client(env->socket, data->client);
		else if (!data->waiting && diff >= TIMEOUT_PING)
		{
			data->waiting = FT_TRUE;
			send_ping(env, data);
		}
	}
}
