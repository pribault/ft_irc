/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 12:37:24 by pribault          #+#    #+#             */
/*   Updated: 2018/04/11 23:29:23 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	recv_bounce(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, env->out, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_SYSTEM,
			"Bounce", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_notice(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, env->out, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_MESSAGE,
			"Notice", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_lusers(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, env->out, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_SYSTEM,
			"Users", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_lops(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, env->out, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_SYSTEM,
			"Operators", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_lchannels(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, env->out, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_SYSTEM,
			"Channels", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}
