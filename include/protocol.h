/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 15:55:08 by pribault          #+#    #+#             */
/*   Updated: 2018/04/02 18:32:59 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOCOL_H
# define PROTOCOL_H

# include "inttypes.h"

typedef enum	e_type
{
	TYPE_STR,
	TYPE_MAX
}				t_type;

typedef struct	s_header
{
	uint64_t	size;
	uint8_t		type;
}				t_header;

#endif
