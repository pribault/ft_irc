/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 20:08:15 by pribault          #+#    #+#             */
/*   Updated: 2018/04/09 12:53:45 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	print_usage(void)
{
	static t_bool	printed = FT_FALSE;

	if (printed == FT_TRUE)
		return ;
	ft_printf("%s./client%s %s<address>%s %s<port>%s %s[options]%s\n",
		COLOR_BOLD, COLOR_CLEAR, COLOR_ITALIC, COLOR_CLEAR, COLOR_ITALIC,
		COLOR_CLEAR, COLOR_ITALIC, COLOR_CLEAR);
	ft_printf(" %savailable options:%s\n", COLOR_HALF, COLOR_CLEAR);
	ft_printf("  %s--help%s or %s-h%s: %sprint usage%s\n", COLOR_UNDERLINED,
		COLOR_CLEAR, COLOR_UNDERLINED, COLOR_CLEAR, COLOR_HALF, COLOR_CLEAR);
	ft_printf("  %s--verbose%s or %s-v%s: %sverbose mode%s\n", COLOR_UNDERLINED,
		COLOR_CLEAR, COLOR_UNDERLINED, COLOR_CLEAR, COLOR_HALF, COLOR_CLEAR);
	ft_printf("  %s--protocol%s <protocool>: %stcp or udp%s\n",
		COLOR_UNDERLINED, COLOR_CLEAR, COLOR_HALF, COLOR_CLEAR);
	ft_printf("  %s--domain%s <domain>: %sipv4 or ipv6%s\n", COLOR_UNDERLINED,
		COLOR_CLEAR, COLOR_HALF, COLOR_CLEAR);
	printed = FT_TRUE;
}

void	get_default(char *s, t_env *env)
{
	static int	state = 0;

	if (!state)
		env->address = s;
	else if (state == 1)
		env->port = s;
	else
		ft_error(2, ERROR_SETTING_DEFAULT, s);
	state++;
}

void	get_protocol(t_env *env, char **args, int n)
{
	(void)n;
	if (!ft_strcmp(args[0], "tcp") || !ft_strcmp(args[0], "TCP"))
		env->protocol = TCP;
	else if (!ft_strcmp(args[0], "udp") || !ft_strcmp(args[0], "UDP"))
		env->protocol = UDP;
	else
		ft_error(2, ERROR_UNKNOWN_PROTOCOL, args[0]);
}

void	get_domain(t_env *env, char **args, int n)
{
	(void)n;
	if (!ft_strcmp(args[0], "ipv4") || !ft_strcmp(args[0], "IPV4"))
		env->domain = IPV4;
	else if (!ft_strcmp(args[0], "ipv6") || !ft_strcmp(args[0], "IPV6"))
		env->domain = IPV6;
	else
		ft_error(2, ERROR_UNKNOWN_DOMAIN, args[0]);
}

void	set_verbose(t_env *env)
{
	env->opt ^= OPT_VERBOSE;
}
