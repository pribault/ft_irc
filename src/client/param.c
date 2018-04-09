/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 19:02:20 by pribault          #+#    #+#             */
/*   Updated: 2018/04/09 23:14:42 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char	*get_param(char *param, char *s)
{
	uint32_t	i;

	param[0] = '\0';
	if (s[0] == ' ')
	{
		i = 0;
		while (s[++i] == ' ')
			;
		if (s[i] == ':')
		{
			while (ft_isof(s[++i], PARAM_WHITE))
				;
		}
		else if (!ft_isof(s[i], PARAM_WHITE) && s[i] != ':')
		{
			while (!ft_isof(s[++i], PARAM_WHITE))
				;
			if (i >= PARAMS_LEN)
				return (NULL);
			ft_memcpy(param, &s[1], i - 1);
			param[i - 1] = '\0';
		}
		return (&s[i]);
	}
	return ((s[0]) ? NULL : s);
}
