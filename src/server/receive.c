/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 08:56:44 by pribault          #+#    #+#             */
/*   Updated: 2018/06/30 15:35:18 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	recv_unknown(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf(
			"[%s%s!%s@%s%s (%s??? %s%s)] %s%s%s\n", COLOR_NAME,
			&data->nickname, data->username, data->hostname, COLOR_CLEAR,
			COLOR_ERROR, &msg->command, COLOR_CLEAR, COLOR_HALF, msg->end,
			COLOR_CLEAR));
}

int		verif_nickname(t_env *env, t_data *data, t_message *msg)
{
	if (!msg->n_params)
	{
		send_error(env, data, ERR_NONICKNAMEGIVEN,
			"no nickname given");
		return (-1);
	}
	if (ft_strlen((char*)&msg->params[0]) >= NICK_MAX_LEN)
	{
		send_error(env, data, ERR_ERRONEUSNICKNAME,
			"nickname too long, max 9 characters");
		return (-1);
	}
	if (is_nickname_valid((char*)&msg->params[0]) == FT_FALSE)
	{
		send_error(env, data, ERR_ERRONEUSNICKNAME,
			"nickname contain invalid characters");
		return (-1);
	}
	return (0);
}

void	recv_nick(t_env *env, t_data *data, t_message *msg)
{
	t_data	*client;
	size_t	i;

	if (verif_nickname(env, data, msg))
		return ;
	i = (size_t)-1;
	while (++i < env->clients.n && (client = client_get_data(
		*(void **)ft_vector_get(&env->clients, i))))
		if (!ft_strcmp(client->nickname, msg->params[0]))
			return (send_error(env, data, ERR_NICKNAMEINUSE, msg->params[0]));
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf(
			"[%s%s!%s@%s%s (%sNick%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
			data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
			COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	if (data->username)
		send_nick(env, data, (char*)&msg->params[0]);
	ft_memcpy(&data->nickname, &msg->params[0],
		ft_strlen((char*)&msg->params[0]) + 1);
	if (data->username && data->nickname)
		send_first_welcome(env, data);
}

void	recv_user(t_env *env, t_data *data, t_message *msg)
{
	t_bool			error;

	error = FT_FALSE;
	if ((msg->n_params < 3 || !msg->end[0]) && (error = FT_TRUE) == FT_TRUE)
		send_error(env, data, ERR_NEEDMOREPARAMS,
			"not enough parameters given");
	if (data->username && (error = FT_TRUE) == FT_TRUE)
		send_error(env, data, ERR_ALREADYREGISTRED,
			"you are already registered");
	if (error == FT_TRUE)
		return ;
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf(
			"[%s%s!%s@%s%s (%sUser%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
			data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
			COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	data->username = ft_strdup((char*)&msg->params[0]);
	data->realname = ft_strdup((char*)&msg->end);
	if (ft_strlen(data->nickname))
		send_first_welcome(env, data);
}

void	recv_list(t_env *env, t_data *data, t_message *msg)
{
	size_t		i;

	if (!data->username)
		send_error(env, data, ERR_NOTREGISTERED,
		"you are not registered");
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf(
		"[%s%s!%s@%s%s (%sList%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
		data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
		COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	i = (size_t)-1;
	send_liststart(env, data);
	while (++i < env->channels.n)
		send_list(env, data, ft_vector_get(&env->channels, i));
	send_listend(env, data);
}
