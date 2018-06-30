/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 12:36:43 by pribault          #+#    #+#             */
/*   Updated: 2018/05/24 16:38:35 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	recv_unknown(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, 1,
		ft_joinf("[%s%s%s (%s??? %s%s)] %s%s%s\n", COLOR_NAME,
			&msg->prefix.name[0], COLOR_CLEAR, COLOR_ERROR, &msg->command,
			COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_welcome(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, 1, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_INFO,
			"Welcome", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_yourhost(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, 1, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_SYSTEM,
			"YourHost", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_created(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, 1, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_SYSTEM,
			"Created", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_myinfo(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, 1, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_SYSTEM,
			"MyInfo", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}
