/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:45:04 by pribault          #+#    #+#             */
/*   Updated: 2018/06/30 12:20:34 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_first_welcome(t_env *env, t_data *data)
{
	send_welcome(env, data);
	send_motdstart(env, data);
	send_motd(env, data);
	send_motdend(env, data);
}

void	send_quit(t_env *env, t_data *data, t_data *to, char *reason)
{
	char	*s;

	if (!(s = ft_joinf(":%s!%s~%s %s :%s%s", data->nickname, data->username,
		data->hostname, QUIT, reason, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, to->client, s, ft_strlen(s));
}

void	send_join(t_env *env, t_data *data, t_data *to, t_channel *channel)
{
	char	*s;

	if (!(s = ft_joinf(":%s!%s~%s %s :%s%s", data->nickname, data->username,
		data->hostname, JOIN, channel->name, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, to->client, s, ft_strlen(s));
}

void	send_who_reply(t_env *env, t_data *data, t_data *client,
		t_channel *channel)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s %s %s %s %s %s H :0 %s%s", env->name,
		RPL_WHOREPLY, channel->name, client->username, client->hostname,
		env->name, client->nickname, client->realname, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_err_no_such_server(t_env *env, t_data *data, char *servname)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s %s :No such server%s", env->name,
		ERR_NOSUCHSERVER, servname, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}
