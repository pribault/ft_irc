/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:46:50 by pribault          #+#    #+#             */
/*   Updated: 2018/04/11 01:00:46 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_error(t_env *env, t_data *data, char *error, char *comment)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s :%s%s", env->name,
		error, comment, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->server, data->client, s, ft_strlen(s));
}

void	send_welcome(t_env *env, t_data *data)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s :Welcome to %s %s!%s@%s%s", env->name,
		RPL_WELCOME, env->name, &data->nickname, data->username,
		data->hostname, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->server, data->client, s, ft_strlen(s));
}

void	send_nick(t_env *env, t_data *data, char *nick)
{
	char	*s;

	if (!(s = ft_joinf(":%s!%s@%s %s :%s%s", &data->nickname, data->username,
		data->hostname, NICK, nick, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->server, data->client, s, ft_strlen(s));
}

void	send_list(t_env *env, t_data *data, t_channel *channel)
{
	char	*s;

	if (!(s = ft_joinf(":%s!%s@%s %s %s %s :%s%s", &data->nickname,
		data->username, data->hostname, RPL_LIST, channel->name,
		channel->perms, channel->topic, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->server, data->client, s, ft_strlen(s));
}

void	send_listend(t_env *env, t_data *data)
{
	char	*s;

	if (!(s = ft_joinf(":%s!%s@%s %s :%s%s", &data->nickname,
		data->username, data->hostname, RPL_LISTEND, "end of channel list",
		CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->server, data->client, s, ft_strlen(s));
}
