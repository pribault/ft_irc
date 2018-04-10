/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 08:56:44 by pribault          #+#    #+#             */
/*   Updated: 2018/04/10 17:10:14 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	recv_unknown(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, env->out,
		ft_joinf("[%s%s%s (%s??? %s%s)] %s%s%s\n", COLOR_NAME,
			&msg->prefix.name[0], COLOR_CLEAR, COLOR_ERROR, &msg->command,
			COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
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
		enqueue_str_by_fd(env, env->out,
		ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n", COLOR_NAME,
			&msg->prefix.name[0], COLOR_CLEAR, COLOR_SYSTEM, &msg->command,
			COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	ft_memcpy(&data->nickname, &msg->params[0],
		ft_strlen((char*)&msg->params[0]));
}

void	recv_user(t_env *env, t_data *data, t_message *msg)
{
	t_bool	error;

	error = FT_FALSE;
	if ((msg->n_params < 3 || !msg->end) && (error = FT_TRUE) == FT_TRUE)
		send_error(env, data, ERR_NEEDMOREPARAMS,
			"not enough parameters given");
	if (data->username && (error = FT_TRUE) == FT_TRUE)
		send_error(env, data, ERR_ALREADYREGISTRED,
			"you are already registered");
	if (error == FT_TRUE)
		return ;
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, env->out,
		ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n", COLOR_NAME,
			&msg->prefix.name[0], COLOR_CLEAR, COLOR_SYSTEM, &msg->command,
			COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
	data->username = ft_strdup((char*)&msg->params[0]);
	data->hostname = ft_strdup((char*)&msg->params[2]);
	if (ft_strlen((char*)&data->nickname))
		send_welcome(env, data);
}
