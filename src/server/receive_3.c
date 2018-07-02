/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 12:29:50 by pribault          #+#    #+#             */
/*   Updated: 2018/07/02 19:18:20 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	set_topic(t_channel *channel, t_message *msg)
{
	char	*s;
	size_t	i;

	i = (size_t)0;
	s = ft_strdup("");
	while (++i < msg->n_params)
	{
		if (!(s = realloc(s, ft_strlen(s) + ft_strlen(msg->params[i] + 2))))
			return (ft_error(2, ERROR_ALLOCATION, NULL));
		if (i > 1)
			ft_memcpy(s, " ", 2);
		ft_memcpy(s + ft_strlen(s), msg->params[i],
			ft_strlen(msg->params[i] + 1));
	}
	if (!(s = realloc(s, ft_strlen(s) + ft_strlen(msg->end) + 2)))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	if (i > 1)
		ft_memcpy(s + ft_strlen(s), " ", 2);
	ft_memcpy(s + ft_strlen(s), msg->end, ft_strlen(msg->end) + 1);
	if (channel->topic)
		free(channel->topic);
	channel->topic = s;
}

void		recv_topic(t_env *env, t_data *data, t_message *msg)
{
	t_channel	*channel;
	size_t		i;

	if (!msg->n_params)
		return (send_error(env, data, RPL_NOTOPIC, "No topic is set"));
	if (msg->n_params == 1 && !ft_strlen(msg->end))
		return (send_error(env, data, ERR_NEEDMOREPARAMS,
			"Not enough parameters"));
		i = (size_t)-1;
	while (++i < env->channels.n &&
		(channel = ft_vector_get(&env->channels, i)))
		if (!ft_strcmp(channel->name, msg->params[0]))
		{
			if (!is_client_in_channel(channel, data))
				return (send_error(env, data, ERR_NOTONCHANNEL,
					"You're not on that channel"));
			else
			{
				set_topic(channel, msg);
				return (send_topic(env, data, channel));
			}
		}
}
