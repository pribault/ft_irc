/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:46:50 by pribault          #+#    #+#             */
/*   Updated: 2018/05/27 11:36:43 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_error(t_env *env, t_data *data, char *error, char *comment)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s :%s%s", env->name,
		error, comment, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_welcome(t_env *env, t_data *data)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s %s :Welcome to %s %s!%s@%s%s", env->name,
		RPL_WELCOME, data->nickname, env->name, &data->nickname,
		data->username, data->hostname, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_nick(t_env *env, t_data *data, char *nick)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s :%s%s", &data->nickname,
		NICK, nick, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_liststart(t_env *env, t_data *data)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s :there is currently %u channels%s",
		&data->nickname, RPL_LISTSTART, env->channels.n, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_list(t_env *env, t_data *data, t_channel *channel)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s %s %s %s :%s%s", &data->nickname, RPL_LIST,
		&data->nickname, channel->name, channel->perms,
		(channel->topic) ? channel->topic : "no topic 😥", CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}
