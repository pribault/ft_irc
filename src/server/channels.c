/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 00:04:45 by pribault          #+#    #+#             */
/*   Updated: 2018/06/30 11:51:56 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_channel	*find_channel(t_vector *vector, char *name)
{
	t_channel	*channel;
	size_t		i;

	i = (size_t)-1;
	while (++i < vector->n && (channel = ft_vector_get(vector, i)))
		if (!ft_strcmp(channel->name, name))
			return (channel);
	return (NULL);
}

void		add_client_to_channel(t_env *env, t_channel *channel, t_data *data)
{
	t_data	**client;
	size_t	i;

	ft_vector_add(&channel->clients, &data);
	i = (size_t)-1;
	while (++i < channel->clients.n &&
		(client = ft_vector_get(&channel->clients, i)))
		send_join(env, data, *client, channel);
}

void		create_channel(t_env *env, t_vector *vector, char *name,
			t_data *data)
{
	t_channel	channel;

	ft_bzero(&channel, sizeof(t_channel));
	channel.name = ft_strdup(name);
	ft_vector_init(&channel.clients, ALLOC_MALLOC, sizeof(t_data *));
	add_client_to_channel(env, &channel, data);
	ft_vector_add(vector, &channel);
}

t_bool		is_client_in_channel(t_channel *channel, t_data *client)
{
	t_data		**data;
	uint64_t	i;

	i = (uint64_t)-1;
	while (++i < channel->clients.n &&
		(data = ft_vector_get(&channel->clients, i)))
		if (client == (*data))
			return (FT_TRUE);
	return (FT_FALSE);
}

void		remove_client_from_channel(t_channel *channel, t_data *client)
{
	t_data		**data;
	uint64_t	i;

	i = (uint64_t)-1;
	while (++i < channel->clients.n &&
		(data = ft_vector_get(&channel->clients, i)))
		if (client == (*data))
			return (ft_vector_del_one(&channel->clients, i));
}
