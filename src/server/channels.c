/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 00:04:45 by pribault          #+#    #+#             */
/*   Updated: 2018/04/11 00:56:05 by pribault         ###   ########.fr       */
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

void		add_client_to_channel(t_channel *channel, t_data *data)
{
	ft_vector_add(&channel->clients, &data);
}

void		create_channel(t_vector *vector, char *name, t_data *data)
{
	t_channel	channel;

	ft_bzero(&channel, sizeof(t_channel));
	channel.name = ft_strdup(name);
	ft_vector_init(&channel.clients, ALLOC_MALLOC, sizeof(t_data *));
	add_client_to_channel(&channel, data);
	ft_vector_add(vector, &channel);
}
