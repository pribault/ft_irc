/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 18:36:05 by pribault          #+#    #+#             */
/*   Updated: 2018/04/08 22:17:14 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_bool		is_host_name_valid(char *s)
{
	uint32_t	i;

	i = 0;
	while (s[i] && i < 25)
	{
		if (!ft_isof(s[i], PARAM_LETTERS) && !ft_isof(s[i], PARAM_NUMBER) &&
			s[i] != '-' && s[i] != '.')
			return (FT_FALSE);
		i++;
	}
	return ((i < 25) ? FT_TRUE : FT_FALSE);
}

t_bool		is_pseudo_valid(char *s)
{
	uint32_t	i;

	if (s[0] && !ft_isof(s[0], PARAM_LETTERS))
		return (FT_FALSE);
	i = 1;
	while (s[i])
	{
		if (!ft_isof(s[i], PARAM_LETTERS) && !ft_isof(s[i], PARAM_NUMBER) &&
			!ft_isof(s[i], PARAM_SPECIAL))
			return (FT_FALSE);
		i++;
	}
	return (FT_TRUE);
}

static char	*prefix_getter(char *prefix, char *s)
{
	uint32_t	i;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '@' && s[i] != '!')
		i++;
	if (i >= PREFIX_MAX)
	{
		ft_printf("here4\n");
		return (NULL);
	}
	ft_memcpy(prefix, s, i);
	prefix[i] = '\0';
	return (s + i);
}

char		*get_prefix(t_prefix *prefix, char *s)
{
	ft_bzero(prefix, sizeof(t_prefix));
	if (!(s = prefix_getter((char*)&prefix->name, s)))
		return (NULL);
	if (*s == '!')
	{
		if (!(s = prefix_getter((char*)&prefix->user, s + 1)))
			return (NULL);
	}
	if (*s == '@')
	{
		if (!(s = prefix_getter((char*)&prefix->host, s + 1)))
			return (NULL);
	}
	return ((*s == ' ') ? s + 1 : NULL);
}
