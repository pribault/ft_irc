/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:45:04 by pribault          #+#    #+#             */
/*   Updated: 2018/04/29 13:46:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_first_welcome(t_env *env, t_data *data)
{
	send_welcome(env, data);
	send_motdstart(env, data);
	send_motd(env, data);
	send_motdend(env, data);
}
