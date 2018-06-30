/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 12:39:00 by pribault          #+#    #+#             */
/*   Updated: 2018/06/30 17:35:02 by pribault         ###   ########.fr       */
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
		RPL_NAMREPLY, channel->name, (*client)->nickname)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	while (++i < channel->clients.n &&
		(client = ft_vector_get(&channel->clients, i)))
	{
		if (!(s = realloc(s, ft_strlen(s) +
			ft_strlen((*client)->nickname) + 2)))
			return (ft_error(2, ERROR_ALLOCATION, NULL));
		ft_memcpy(s + ft_strlen(s) + 1, (*client)->nickname,
			ft_strlen((*client)->nickname) + 1);
		s[ft_strlen(s)] = ' ';
	}
	if (!(s = realloc(s, ft_strlen(s) + CRLF_SIZE + 1)))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	ft_memcpy(s + ft_strlen(s), CRLF, CRLF_SIZE + 1);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_privmsg_user(t_env *env, t_data *data, t_data *to,
		t_message *msg)
{
	char	*s;
	size_t	i;

	if (!(s = ft_joinf(":%s!%s~%s %s %s", data->nickname, data->username,
		data->hostname, PRIVMSG, msg->params[0])))
		ft_error(2, ERROR_ALLOCATION, NULL);
	i = 0;
	while (++i < msg->n_params)
	{
		if (!(s = realloc(s, ft_strlen(s) +
			ft_strlen(msg->params[i]) + 2)))
			return (ft_error(2, ERROR_ALLOCATION, NULL));
		ft_memcpy(s + ft_strlen(s) + 1, msg->params[i],
			ft_strlen(msg->params[i]) + 1);
		s[ft_strlen(s)] = ' ';
	}
	if (!(s = realloc(s, ft_strlen(s) + ft_strlen(msg->end) + CRLF_SIZE + 3)))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	ft_memcpy(s + ft_strlen(s), " :", 3);
	ft_memcpy(s + ft_strlen(s), msg->end, ft_strlen(msg->end) + 1);
	ft_memcpy(s + ft_strlen(s), CRLF, CRLF_SIZE + 1);
	ft_printf("%s\n", s);
	enqueue_write(env->socket, to->client, s, ft_strlen(s));
}

void	send_privmsg_channel(t_env *env, t_data *data, t_channel *channel,
		t_message *msg)
{
	t_data	**client;
	size_t	i;

	i = (size_t)-1;
	while (++i < channel->clients.n &&
		(client = ft_vector_get(&channel->clients, i)))
		send_privmsg_user(env, data, *client, msg);
}
