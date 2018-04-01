/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:38:42 by pribault          #+#    #+#             */
/*   Updated: 2018/04/01 19:39:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static t_short_flag	g_short_flags[] =
{
	{0, NULL}
};

static t_long_flag	g_long_flags[] =
{
	{NULL, 0, {0}, NULL}
};

void	init_env(t_env *env, int argc, char **argv)
{
	if (!(env->server = server_new()))
		ft_error(2, ERROR_ALLOCATION, NULL);
	ft_get_flags(argc, argv, ft_get_flag_array((void*)&g_short_flags,
		(void*)&g_long_flags, NULL), env);
}

int		main(int argc, char **argv)
{
	t_env	env;

	init_env(&env, argc, argv);
	return (0);
}
