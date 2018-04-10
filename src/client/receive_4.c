/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:35:26 by pribault          #+#    #+#             */
/*   Updated: 2018/04/10 13:38:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	recv_error(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, env->out, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_ERROR,
			"Error", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}
