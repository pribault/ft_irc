/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 12:36:43 by pribault          #+#    #+#             */
/*   Updated: 2018/04/09 12:37:48 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	recv_welcome(t_env *env, t_data *data, t_message *msg)
{
	(void)env;
	(void)data;
	ft_printf("[%s%s%s (%s%s%s)] ",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR,
		COLOR_WLCM, "Welcome", COLOR_CLEAR);
	ft_printf("%s%s%s\n", COLOR_HALF, msg->end, COLOR_CLEAR);
}

void	recv_yourhost(t_env *env, t_data *data, t_message *msg)
{
	(void)env;
	(void)data;
	ft_printf("[%s%s%s (%s%s%s)] ",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR,
		COLOR_YHST, "YourHost", COLOR_CLEAR);
	ft_printf("%s%s%s\n", COLOR_HALF, msg->end, COLOR_CLEAR);
}

void	recv_created(t_env *env, t_data *data, t_message *msg)
{
	(void)env;
	(void)data;
	ft_printf("[%s%s%s (%s%s%s)] ",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR,
		COLOR_CRTD, "Created", COLOR_CLEAR);
	ft_printf("%s%s%s\n", COLOR_HALF, msg->end, COLOR_CLEAR);
}

void	recv_myinfo(t_env *env, t_data *data, t_message *msg)
{
	(void)env;
	(void)data;
	ft_printf("[%s%s%s (%s%s%s)] ",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR,
		COLOR_CRTD, "MyInfo", COLOR_CLEAR);
	ft_printf("%s%s%s\n", COLOR_HALF, msg->end, COLOR_CLEAR);
}

void	recv_bounce(t_env *env, t_data *data, t_message *msg)
{
	(void)env;
	(void)data;
	ft_printf("[%s%s%s (%s%s%s)] ",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR,
		COLOR_CRTD, "Bounce", COLOR_CLEAR);
	ft_printf("%s%s%s\n", COLOR_HALF, msg->end, COLOR_CLEAR);
}
