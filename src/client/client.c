/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:38:42 by pribault          #+#    #+#             */
/*   Updated: 2018/04/02 12:26:53 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static t_short_flag	g_short_flags[] =
{
	{'h', (void*)&print_usage},
	{0, NULL}
};

static t_long_flag	g_long_flags[] =
{
	{"help", 0, {0}, (void*)&print_usage},
	{NULL, 0, {0}, NULL}
};

static t_error	g_errors[] =
{
	{ERROR_SETTING_DEFAULT, "'%s' address and port already set", 0},
	{0, NULL, 0}
};

void	init_env(t_env *env, int argc, char **argv)
{
	ft_add_errors((t_error*)&g_errors);
	if (!(env->server = server_new()))
		ft_error(2, ERROR_ALLOCATION, NULL);
	env->address = NULL;
	env->port = NULL;
	ft_get_flags(argc, argv, ft_get_flag_array((void*)&g_short_flags,
		(void*)&g_long_flags, (void*)&get_default), env);
}

int		main(int argc, char **argv)
{
	t_env	env;

	init_env(&env, argc, argv);
	return (0);
}
