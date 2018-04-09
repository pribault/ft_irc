/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:34:31 by pribault          #+#    #+#             */
/*   Updated: 2018/04/09 17:39:43 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	recv_motdstart(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, env->out, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_INFO,
			"MotdStart", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_motdend(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, env->out, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_INFO,
			"MotdEnd", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_lme(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, env->out, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_SYSTEM,
			"Server", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}
