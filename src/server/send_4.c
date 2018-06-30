/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 12:39:00 by pribault          #+#    #+#             */
/*   Updated: 2018/06/30 13:13:58 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_end_of_who(t_env *env, t_data *data, char *name)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s %s :End of WHO list%s", env->name,
		RPL_ENDOFWHO, name, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_topic(t_env *env, t_data *data, t_channel *channel)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s %s :%s%s", env->name,
		RPL_TOPIC, channel->name, channel->topic, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_name_reply(t_env *env, t_data *data, t_channel *channel)
{
	t_data	**client;
	char	*s;
	size_t	i;

	i = (size_t)0;
	if (!(client = ft_vector_get(&channel->clients, 0)))
		return ;
	if (!(s = ft_joinf(":%s %s = %s :%s", env->name,
		RPL_TOPIC, channel->name, (*client)->nickname)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	while (++i < channel->clients.n &&
		(client = ft_vector_get(&channel->clients, i)))
	{
		if (!(s = realloc(s, ft_strlen(s) +
			ft_strlen((*client)->nickname) + 2)))
			return (ft_error(2, ERROR_ALLOCATION, NULL));
		s[ft_strlen(s)] = ' ';
		ft_memcpy(s + ft_strlen(s) + 1, (*client)->nickname,
			ft_strlen((*client)->nickname) + 1);
	}
	if (!(s = realloc(s, ft_strlen(s) + CRLF_SIZE + 1)))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	ft_memcpy(s + ft_strlen(s), CRLF, CRLF_SIZE + 1);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}
