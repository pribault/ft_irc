/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rfc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 10:39:27 by pribault          #+#    #+#             */
/*   Updated: 2018/04/07 21:04:42 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RFC_H
# define RFC_H

/*
***************
**	defines  **
***************
*/

/*
**	register protocol:
**		PASS
**		NICK
**		USER
**
**	PASS is optionnal
*/

# define PASS		"PASS"
# define NICK		"NICK"
# define USER		"USER"

/*
**	ping poooooong
*/

# define PING		"PING"
# define PONG		"PONG"

/*
**	messages
*/

# define NOTICE		"NOTICE"

/*
**	responses
*/

# define RPL_NONE	"RPL_NONE"

/*
**	message separator
*/

# define CRLF		"\r\n"
# define CRLF_SIZE	2

/*
**	parameter separator
*/

# define SPACE		" "

/*
**	paramters types
*/

# define PARAM_NUMBER	"0123456789"
# define PARAM_LETTERS	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define PARAM_SPECIAL	"-[]\\`^{}"
# define PARAM_WHITE	" \r\n"

/*
**	message formatage
*/

# define PREFIX_MAX		64

# define COMMAND_MAX	16

typedef enum		e_prefix_type
{
	PREFIX_SERVER,
	PREFIX_USER,
	PREFIX_HOST
}					t_prefix_type;

typedef struct		s_prefix
{
	char			*name;
	t_prefix_type	type;
}					t_prefix;

typedef struct		s_command
{
	char			*command;
}					t_command;

typedef struct		s_message
{
	t_prefix		*prefix;
	t_command		*command;
}					t_message;

#endif
