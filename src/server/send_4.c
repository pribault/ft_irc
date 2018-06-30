/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 12:39:00 by pribault          #+#    #+#             */
/*   Updated: 2018/06/30 12:41:46 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_end_of_who(t_env *env, t_data *data, char *name)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s %s :End of WHO list%s", env->name,
		RPL_ENDOFWHO, name, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}
