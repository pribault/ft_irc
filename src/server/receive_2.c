/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 18:39:44 by pribault          #+#    #+#             */
/*   Updated: 2018/07/02 19:16:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	recv_join(t_env *env, t_data *data, t_message *msg)
{
	char		**array;
	t_channel	*channel;
	uint32_t	i;

	if (!(array = ft_multisplit((char*)&msg->params[0], ",")))
		ft_error(2, ERROR_ALLOCATION, NULL);
	i = (uint32_t)-1;
	while (array[++i])
	{
		if ((channel = find_channel(&env->channels, array[i])) &&
			!is_client_in_channel(channel, data))
			add_client_to_channel(env, channel, data);
		else
			create_channel(env, &env->channels, array[i], data);
	}
	ft_free_array((void**)array, ft_arraylen(array) + 1);
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf(
		"[%s%s!%s@%s%s (%sJoin%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
		data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
		COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_quit(t_env *env, t_data *data, t_message *msg)
{
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf(
		"[%s%s!%s@%s%s (%sQuit%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
		data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
		COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	notify_disconnection(env, data, msg->end);
	socket_remove_client(env->socket, data->client);
}

void	recv_who(t_env *env, t_data *data, t_message *msg)
{
	t_channel	*channel;
	t_data		**client;
	size_t		i;
	size_t		j;

	if (!msg->n_params)
		return (send_err_no_such_server(env, data, "None"));
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf(
		"[%s%s!%s@%s%s (%sWho%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
		data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
		COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	i = (size_t)-1;
	while (++i < env->channels.n &&
		(channel = ft_vector_get(&env->channels, i)))
		if (!ft_strcmp(channel->name, msg->params[0]))
		{
			j = (size_t)-1;
			while (++j < channel->clients.n &&
				(client = ft_vector_get(&channel->clients, j)))
				send_who_reply(env, data, *client,
					channel);
			return (send_end_of_who(env, data, channel->name));
		}
	send_err_no_such_server(env, data, msg->params[0]);
}

void	recv_ping(t_env *env, t_data *data, t_message *msg)
{
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf(
		"[%s%s!%s@%s%s (%sPing%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
		data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
		COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	send_pong(env, data);
}

void	recv_privmsg(t_env *env, t_data *data, t_message *msg)
{
	t_channel	*channel;
	t_data		*client;
	size_t		i;

	if (!msg->n_params)
		return (send_error(env, data, ERR_NORECIPIENT,
			"No recipient given PRIVMSG"));
		if (msg->n_params == 1 && !ft_strlen(msg->end))
		return (send_error(env, data, ERR_NOTEXTTOSEND,
			"No text to send"));
		i = (size_t)-1;
	while (++i < env->clients.n &&
		(client = client_get_data(*(void **)ft_vector_get(&env->clients, i))))
		if (!ft_strcmp(client->nickname, msg->params[0]))
			return (send_privmsg_user(env, data, client, msg));
	i = (size_t)-1;
	while (++i < env->channels.n &&
		(channel = ft_vector_get(&env->channels, i)))
		if (!ft_strcmp(channel->name, msg->params[0]))
			return (send_privmsg_channel(env, data, channel, msg));
	send_no_such_nick(env, data, msg->params[0]);
}
