/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 17:10:30 by pribault          #+#    #+#             */
/*   Updated: 2018/04/02 17:23:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	enqueue_str_by_fd(t_env *env, int fd, char *s)
{
	t_msg	msg;

	msg = (t_msg){s, ft_strlen(s)};
	server_enqueue_write_by_fd(env->server, fd, &msg);
}
