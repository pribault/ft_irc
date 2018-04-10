/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 23:50:53 by pribault          #+#    #+#             */
/*   Updated: 2018/04/10 23:54:29 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void				cmd_nick(t_env *env, char *s)
{
	send_nick(env->server, env->client, s);
}

void				cmd_list(t_env *env, char *s)
{
	(void)s;
	send_list(env->server, env->client);
}

void				cmd_join(t_env *env, char *s)
{
	(void)s;
	send_join(env->server, env->client, s);
}
