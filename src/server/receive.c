/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 08:56:44 by pribault          #+#    #+#             */
/*   Updated: 2018/04/10 08:57:08 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	recv_unknown(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, env->out,
		ft_joinf("[%s%s%s (%s??? %s%s)] %s%s%s\n", COLOR_NAME,
			&msg->prefix.name[0], COLOR_CLEAR, COLOR_ERROR, &msg->command,
			COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}
