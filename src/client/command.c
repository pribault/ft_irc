/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 18:39:27 by pribault          #+#    #+#             */
/*   Updated: 2018/04/11 14:46:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char	*get_command(char *command, char *s)
{
	uint32_t	i;

	*command = '\0';
	if (ft_isof(s[0], PARAM_LETTERS))
	{
		i = 1;
		while (s[i] && ft_isof(s[i], PARAM_LETTERS))
			i++;
		if (i >= COMMAND_MAX - 1)
			return (NULL);
		ft_memcpy(command, s, i);
		command[i] = '\0';
		return (&s[i]);
	}
	else if (ft_isof(s[0], PARAM_NUMBER) && ft_isof(s[1], PARAM_NUMBER) &&
		ft_isof(s[2], PARAM_NUMBER))
	{
		ft_memcpy(command, s, 3);
		command[3] = '\0';
		return (&s[3]);
	}
	return (NULL);
}
