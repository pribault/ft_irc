/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 19:02:20 by pribault          #+#    #+#             */
/*   Updated: 2018/04/29 12:11:57 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char	*get_param(char *param, char *s)
{
	uint32_t	i;

	param[0] = '\0';
	if (s[0] == ' ')
	{
		while (*(++s) == ' ')
			;
		i = 0;
		if (s[i] == ':')
			i++;
		else if (!ft_isof(s[i], PARAM_WHITE) && s[i] != ':')
		{
			while (s[i] && !ft_isof(s[++i], PARAM_WHITE))
				;
			if (i >= PARAMS_LEN - 1)
				return (NULL);
			ft_memcpy(param, s, i);
			param[i] = '\0';
		}
		return (&s[i]);
	}
	return ((!s[0]) ? s : NULL);
}
