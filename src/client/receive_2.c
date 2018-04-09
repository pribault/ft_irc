/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 12:37:24 by pribault          #+#    #+#             */
/*   Updated: 2018/04/09 12:50:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	recv_notice(t_env *env, t_data *data, t_message *msg)
{
	(void)env;
	(void)data;
	ft_printf("[%s%s%s (%s%s%s)] ",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR,
		COLOR_NOTICE, "Notice", COLOR_CLEAR);
	ft_printf("%s%s%s\n", COLOR_HALF, msg->end, COLOR_CLEAR);
}

void	recv_lusers(t_env *env, t_data *data, t_message *msg)
{
	(void)env;
	(void)data;
	ft_printf("[%s%s%s (%s%s%s)] ",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR,
		COLOR_MOTD, "Users", COLOR_CLEAR);
	ft_printf("%s%s%s\n", COLOR_HALF, msg->end, COLOR_CLEAR);
}

void	recv_lops(t_env *env, t_data *data, t_message *msg)
{
	(void)env;
	(void)data;
	ft_printf("[%s%s%s (%s%s%s)] ",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR,
		COLOR_MOTD, "Operators", COLOR_CLEAR);
	ft_printf("%s%s%s\n", COLOR_HALF, msg->end, COLOR_CLEAR);
}

void	recv_motd(t_env *env, t_data *data, t_message *msg)
{
	(void)env;
	(void)data;
	ft_printf("[%s%s%s (%s%s%s)] ",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR,
		COLOR_MOTD, "Motd", COLOR_CLEAR);
	ft_printf("%s%s%s\n", COLOR_HALF, msg->end, COLOR_CLEAR);
}
