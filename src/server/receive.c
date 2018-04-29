/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 08:56:44 by pribault          #+#    #+#             */
/*   Updated: 2018/04/29 13:46:40 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	recv_unknown(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, env->out, ft_joinf(
			"[%s%s!%s@%s%s (%s??? %s%s)] %s%s%s\n", COLOR_NAME,
			&data->nickname, data->username, data->hostname, COLOR_CLEAR,
			COLOR_ERROR, &msg->command, COLOR_CLEAR, COLOR_HALF, msg->end,
			COLOR_CLEAR));
}

void	recv_nick(t_env *env, t_data *data, t_message *msg)
{
	t_bool	error;

	error = FT_FALSE;
	if (!msg->n_params && (error = FT_TRUE) == FT_TRUE)
		send_error(env, data, ERR_NONICKNAMEGIVEN,
			"no nickname given");
	if (ft_strlen((char*)&msg->params[0]) >= NICK_MAX_LEN &&
		(error = FT_TRUE) == FT_TRUE)
		send_error(env, data, ERR_ERRONEUSNICKNAME,
			"nickname too long, max 9 characters");
	if (is_nickname_valid((char*)&msg->params[0]) == FT_FALSE &&
		(error = FT_TRUE) == FT_TRUE)
		send_error(env, data, ERR_ERRONEUSNICKNAME,
			"nickname contain invalid characters");
	if (error == FT_TRUE)
		return ;
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, env->out, ft_joinf(
			"[%s%s!%s@%s%s (%sNick%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
			data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
			COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	if (data->username)
		send_nick(env, data, (char*)&msg->params[0]);
	ft_memcpy(&data->nickname, &msg->params[0],
		ft_strlen((char*)&msg->params[0]) + 1);
}

void	recv_user(t_env *env, t_data *data, t_message *msg)
{
	struct hostent	*host;
	t_addr			*addr;
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
		enqueue_str_by_fd(env, env->out, ft_joinf(
			"[%s%s!%s@%s%s (%sUser%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
			data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
			COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	data->username = ft_strdup((char*)&msg->params[0]);
	data->hostname = ft_strdup((char*)&msg->params[2]);
	addr = client_get_address(data->client);
	if ((host = gethostbyaddr(&addr->addr, addr->len, env->domain)))
		data->hostname = ft_strdup(host->h_name);
	if (ft_strlen((char*)&data->nickname))
		send_first_welcome(env, data);
}

void	recv_list(t_env *env, t_data *data, t_message *msg)
{
	size_t		i;

	if (!data->username)
		send_error(env, data, ERR_NOTREGISTERED,
		"you are not registered");
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, env->out, ft_joinf(
		"[%s%s!%s@%s%s (%sList%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
		data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
		COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	i = (size_t)-1;
	send_liststart(env, data);
	while (++i < env->channels.n)
		send_list(env, data, ft_vector_get(&env->channels, i));
	send_listend(env, data);
}

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
		if ((channel = find_channel(&env->channels, array[i])))
			add_client_to_channel(channel, data);
		else
			create_channel(&env->channels, array[i], data);
	}
	ft_free_array((void**)array, ft_arraylen(array) + 1);
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, env->out, ft_joinf(
		"[%s%s!%s@%s%s (%sJoin%s)] %s%s%s\n", COLOR_NAME, &data->nickname,
		data->username, data->hostname, COLOR_CLEAR, COLOR_SYSTEM,
		COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}
