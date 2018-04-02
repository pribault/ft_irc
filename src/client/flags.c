/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 20:08:15 by pribault          #+#    #+#             */
/*   Updated: 2018/04/02 10:02:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	print_usage(void)
{
	ft_printf("%s./client%s %s<address>%s %s<port>%s %s[options]%s\n",
		COLOR_BOLD, COLOR_CLEAR, COLOR_ITALIC, COLOR_CLEAR, COLOR_ITALIC,
		COLOR_CLEAR, COLOR_ITALIC, COLOR_CLEAR);
	ft_printf(" %savailable options:%s\n", COLOR_HALF, COLOR_CLEAR);
	ft_printf("  %s--help%s or %s-h%s: %sprint usage%s\n", COLOR_UNDERLINED,
		COLOR_CLEAR, COLOR_UNDERLINED, COLOR_CLEAR, COLOR_HALF, COLOR_CLEAR);
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
