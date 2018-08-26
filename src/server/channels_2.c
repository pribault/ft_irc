/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 16:07:44 by pribault          #+#    #+#             */
/*   Updated: 2018/08/25 16:22:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	remove_channel(t_env *env, t_channel *channel)
{
	t_channel	*chan;
	size_t		i;

	i = (size_t)-1;
	while (++i < env->channels.n && (chan = ft_vector_get(&env->channels, i)))
		if (!ft_strcmp(chan->name, channel->name))
			ft_vector_del_one(&env->channels, i--);
}

void	part_channel(t_env *env, t_data *client, t_channel *channel)
{
	t_data	**to;
	size_t	i;

	i = (size_t)-1;
	while (++i < channel->clients.n)
		if ((to = ft_vector_get(&channel->clients, i)) &&
			*to != client)
			send_part(env, client, *to, channel);
}
