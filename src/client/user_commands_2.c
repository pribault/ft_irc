/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_commands_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 11:26:40 by pribault          #+#    #+#             */
/*   Updated: 2018/05/24 15:50:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	cmd_connect(t_env *env, char *s)
{
	char	**array;

	if (env->client)
		return (ft_error(2, ERROR_ALREADY_CONNECTED, env->address));
	if (!(array = ft_multisplit(s, WHITESPACES)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	if (ft_arraylen(array) != 2)
		ft_error(2, ERROR_INVALID_PARAMETERS, "/connect <address> <port>");
	else if (!(socket_connect(env->socket,
		(t_method){env->protocol, env->domain}, array[0],
		array[1])))
		return (ft_error(2, ERROR_CANNOT_CONNECT, array[0]));
	ft_free_array((void**)array, ft_arraylen(array) + 1);
}
